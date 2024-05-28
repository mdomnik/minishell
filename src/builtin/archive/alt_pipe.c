static int	wait_processes(t_shell *shell)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	save_status = 0;
	wpid = 0;
	while (wpid != -1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == shell->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

void    pip_exe(t_shell *shell, int i, int j, int *fd)
{
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
        if (dup2(shell->fd[j], 1) == -1)
            perror("error2");
    }
    close(fd[0]);
    close(fd[1]);
}

int pipex(t_shell *shell)
{
    int status;
    int fd[2];

    if (pipe(fd) == -1)
        perror("pipe error");
    shell->pid = fork();
    if (shell->pid == 0)
    {
        if (cmp_str(shell->parser->i_str, "STDIN") == 0
            && cmp_str(shell->parser->o_str, "PIPE") == 0)
            pip_exe(shell, 1, -1, fd);
        if (cmp_str(shell->parser->i_str, "PIPE") == 0
            && cmp_str(shell->parser->o_str, "STDOUT") == 0)
            pip_exe(shell, 0, -1, fd);
        else
            pip_exe(shell, 1, 0, fd);
    }
    if (!shell->parser->next)
        return (-2);
    shell->parser = shell->parser->next;
    status = wait_processes(shell);
    close(fd[0]);
    close(fd[1]);
    return (status);
}