/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:33:36 by kaan              #+#    #+#             */
/*   Updated: 2024/06/21 14:46:10 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

bool	is_valid_id(char *token)
{
	size_t	i;

	i = 0;
	if (strcmp_msn(token, "="))
		return (false);
	while (token[i] && token[i] != '=')
	{
		if (ft_isdigit(token[i]) || token[i] == '!' || token[i] == '@'
			|| token[i] == '{' || token[i] == '}' || token[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

int	find_builtin(t_shell *shell, t_exec *exec)
{
	char	*cmd;

	cmd = exec->token[0];
	if (cmp_str(cmd, "echo") == 0)
		return(builtin_echo(exec));
	else if (cmp_str(cmd, "env") == 0)
		return(builtin_env(shell, exec));
	else if (cmp_str(cmd, "exit") == 0)
		builtin_exit(shell, exec);
	else if (cmp_str(cmd, "export") == 0)
		return(builtin_export(shell, exec));
	else if (cmp_str(cmd, "pwd") == 0)
		return(builtin_pwd(shell));
	else if (cmp_str(cmd, "unset") == 0)
		return(builtin_unset(shell, exec));
	else if (cmp_str(cmd, "cd") == 0)
		return(builtin_cd(shell, exec));
	else
		return (2);
	return (1);
}

void	single_exe(t_shell *shell, t_exec *exec)
{
	if (find_builtin(shell, exec) == 0)
	{
		free_shell(shell);
		exit (EXIT_SUCCESS) ;
	}
	find_path(shell, exec);
}

void	exec_cmd(t_shell *shell, t_exec *exec)
{
	signal(SIGINT, child_signals);
	if (exec->operator == PIPE)
		pipe_exe(shell, exec);
	else if (exec->operator == NONE)
		single_exe(shell, exec);
	else
		redir_exe(shell, exec);
	free_shell(shell);
	exit(exit_status);
}

void	execution(t_shell *shell)
{
	t_exec	*exec;
	int			status;
	int			ret;
	exec = shell->exec;
	if (exec_size(exec) == 1)
	{
		ret = find_builtin(shell, exec);
		if (ret == 2)
		{
			if (fork() == 0)
			{
				signal(SIGINT, child_signals);
				find_path(shell, exec);
			}
		}
		else if (ret == -1)
		{
			*(shell->exit_status) = 1;
			execfreelist_ms(&shell->exec);
			reset_loop(shell);
			return ;
		}
	}
	else if (fork() == 0)
		exec_cmd(shell, exec);
	waitpid(-1, &status, 0);
	if (!WTERMSIG(status))
	{
		*(shell->exit_status) = status / 256;
	}
	execfreelist_ms(&shell->exec);
	reset_loop(shell);
}
