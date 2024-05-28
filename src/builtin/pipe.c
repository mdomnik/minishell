#include "../../inc/minishell.h"

void cmd_count(t_shell *shell)
{
	t_parser	*current;
	int			i;
    int         n;

	current = shell->parser;
    i = 0;
	if (shell->parser == NULL)
		printf("Stack is empty\n");
	while (current != NULL)
	{
        if (current->cmd)
            i++;	
		current = current->next;
	}
    shell->fd = malloc(sizeof(int) * i * 2);
    n = 0;
    while (n != i)
    {
        pipe(shell->fd + n * 2);
        n++;
    }
    shell->cmd_count = malloc(sizeof(int));
    *(shell->cmd_count) = i;
}

void    fd_close(t_shell *shell)
{
    int i;

    i = 0;
    while (i != (*(shell->cmd_count) - 1) * 2)
    {
        if (close(shell->fd[i]) == -1)
            perror("close error");
        i++;
    }
}

void    pip_exe(t_shell *shell, int i, int j, int pid)
{
    shell->pid = pid;
    if ((i == 1 && j == -1) 
        || (i == 0 && j == -1))
    {
        if (dup2(shell->fd[i], i) == -1)
            perror("error2");
    }
    else if (j == -1)
    {
        if (dup2(shell->fd[i], 0) == -1)
            perror("error2");
        i += 2;
    }
    else
    {
        if (dup2(shell->fd[i], 0) == -1)
            perror("error2");
        if (dup2(shell->fd[i + 3], 1) == -1)
            perror("error2");
    }
    fd_close(shell);
    find_builtin(shell);
}

void pipex(t_shell *shell)
{
    pid_t   *pid_array;
    pid_t   pid;
    int     status;
    int     i;

    //print_parser(shell);
    i = 0;
    shell->pid = -1;
    cmd_count(shell);
    pid_array = malloc(sizeof(pid_t) * *(shell->cmd_count) + 2);
    while (shell->parser)
    {
        pid = fork();
        if (pid == -1)
            perror("fork error");
        else if (pid > 0)
        {
            pid_array[i] = pid;
            i++;
            if (i == *(shell->cmd_count))
                pid_array[i] = -1;
        }
        else if (pid == 0)
        {
            if (cmp_str(shell->parser->i_str, "STDIN") == 0
                    && cmp_str(shell->parser->o_str, "PIPE") == 0)
                    pip_exe(shell, 1, -1, pid);
            else if (cmp_str(shell->parser->i_str, "PIPE") == 0
                && cmp_str(shell->parser->o_str, "STDOUT") == 0)
                pip_exe(shell, (shell->parser->index - 1) * 2, -1, pid);
            else
                pip_exe(shell, (shell->parser->index - 1) * 2, 0, pid);
        }
        shell->parser = shell->parser->next;
    }
    //ft_waitpid(pid_array);
    waitpid(-1, &status, 0);
    fd_close(shell);
    reset_loop(shell, NULL);
}
