/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:00:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/04 17:43:58 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pip_exe(t_shell *shell, int i, int j)
{
	if ((i == 1 && j == -1) 
		|| (i == 0 && j == -1))
	{
		if (dup2(shell->fd[i], i) == -1)
			perror("error2");
	}
	else if (j == -1)
	{
		if (dup2(shell->fd[i], STDIN_FILENO) == -1)
			perror("error2");
		i += 2;
	}
	else
	{
		if (dup2(shell->fd[i], STDIN_FILENO) == -1)
			perror("error2");
		if (dup2(shell->fd[i + 3], STDOUT_FILENO) == -1)
			perror("error2");
	}
	fd_close(shell);
	find_builtin(shell);
}

void	less(t_shell *shell, int i)
{
	if (shell->parser->index != 0)
	{
		if (dup2(shell->fd[i], STDOUT_FILENO) == -1)
			perror("great error1");
	}
	if (dup2(*(shell->red_fd), STDIN_FILENO) == -1)
		perror("great error2");
	fd_close(shell);
	find_builtin(shell);
}

void	great(t_shell *shell, int i)
{
	if (cmp_str(shell->parser->i_str, "PIPE") == 0
		&& shell->parser->cmd == NULL)
	{
		fd_close(shell);
		reset_loop(shell, NULL, shell->parser->cmd, 0);
	}
	if (dup2(shell->fd[i], STDIN_FILENO) == -1)
		perror("great error1");
	if (dup2(*(shell->red_fd), STDOUT_FILENO) == -1)
		perror("great error2");
	fd_close(shell);
	find_builtin(shell);
}

void	heredoc(t_shell *shell)
{
	if (dup2(*(shell->red_fd), 1) == -1)
		perror("great error2");
	fd_close(shell);
	find_builtin(shell);
}

void	handle_here_document(t_shell *shell)
{
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	set_signals_child();
	*(shell->red_fd) = open("/tmp/heredoc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (*(shell->red_fd) == -1)
		err_fd();
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (strcmp_ms(line, shell->parser->i_str) == 0)
			break ;
		write(*(shell->red_fd), line, ft_strlen(line));
		write(*(shell->red_fd), "\n", 1);
		free(line);
	}
}
