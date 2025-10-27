/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:45:51 by kaan              #+#    #+#             */
/*   Updated: 2025/10/27 18:22:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	left_side(t_exec *exec, t_shell *shell, int pipe_fd[2])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_cmd(shell, exec);
}

void	right_side(t_exec *exec, t_shell *shell, int pipe_fd[2])
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_cmd(shell, exec);
}

void	pipe_exe(t_shell *shell, t_exec *exec)
{
	pid_t	child_pid;
	int		pipe_fd[2];
	int		status;

	exec->operator = NONE;
	if (pipe(pipe_fd) == -1)
		exit_shell(shell, "PIPE_ERR", EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == -1)
		exit_shell(shell, "FORK_ERR", EXIT_FAILURE);
	if (child_pid == 0)
		left_side(exec, shell, pipe_fd);
	right_side(exec->next, shell, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child_pid, &status, 0);
	*(shell->exit_status) = status / 256;
}
