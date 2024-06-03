/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:00:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/03 14:40:54 by kaan             ###   ########.fr       */
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

void	less(t_shell *shell, int i)
{
	if (shell->parser->index != 0)
	{
		if (dup2(shell->fd[i], 1) == -1)
			perror("great error1");
	}
	if (dup2(*(shell->red_fd), 0) == -1)
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
		reset_loop(shell, NULL);
	}
	if (dup2(shell->fd[i], 0) == -1)
		perror("great error1");
	if (dup2(*(shell->red_fd), 1) == -1)
		perror("great error2");
	fd_close(shell);
	find_builtin(shell);
}

void	handle_here_document(t_shell *shell)
{
	char	*line;
	size_t	len;
	ssize_t	read;

	line = NULL;
	len = 0;
	*(shell->red_fd) = open("/tmp/heredoc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (*(shell->red_fd) == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("heredoc> ");
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		if (strncmp(line, shell->parser->i_str,
				strlen(shell->parser->i_str)) == 0
			&& line[strlen(shell->parser->i_str)] == '\n')
			break ;
		write(*(shell->red_fd), line, read);
		printf("heredoc> ");
	}
	free(line);
	close(*(shell->red_fd));
	*(shell->red_fd) = open("/tmp/heredoc_tmp", O_RDONLY);
	if (*(shell->red_fd) == -1)
	{
		perror("open temp file for read");
		exit(EXIT_FAILURE);
	}
}
