/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:54:22 by kaan              #+#    #+#             */
/*   Updated: 2024/06/04 17:13:55 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	c_c_great(t_shell *shell, t_parser *current)
{
	int			fd;
	int			r;

	r = 0;
	while (cmp_str(current->files[r], current->o_str) != 0)
	{
		fd = open(current->files[r], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			err_fd();
		close(fd);
		r++;
	}
	if (cmp_str(current->files[r], current->o_str) == 0)
	{
		if (current->file_types[r] == 2)
			*(shell->red_fd) = open(current->files[r],
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (current->file_types[r] == 5)
			*(shell->red_fd) = open(current->files[r],
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*(shell->red_fd) == -1)
			err_fd();
	}
}

void	c_c_less(t_shell *shell, t_parser *current)
{
	/*if (current->cmd == NULL)
		reset_loop(shell, "command not found");*/
	*(shell->red_fd) = open(current->i_str, O_RDONLY);
	if (*(shell->red_fd) == -1)
		err_fd();
}

void	c_c_cmd_count_value_store(t_shell *shell, int i)
{
	int		n;

	shell->fd = malloc(sizeof(int) * i * 2);
	n = 0;
	while (n != i)
	{
		pipe(shell->fd + n * 2);
		n++;
	}
	*(shell->cmd_count) = i;
}

void	cmd_count(t_shell *shell)
{
	t_parser	*current;
	int			i;

	i = 0;
	current = shell->parser;
	shell->red_fd = malloc(sizeof(int));
	*(shell->red_fd) = -2;
	if (current == NULL)
		printf("Stack is empty\n");
	while (current != NULL)
	{
		if (current->i_str != NULL)
			i++;
		if (current->output == T_GREATER
			|| current->output == T_APPEND)
			c_c_great(shell, current);
		else if (current->input == T_LESSER)
			c_c_less(shell, current);
		else if (current->input == T_HEREDOC)
			handle_here_document(shell);
		current = current->next;
	}
	c_c_cmd_count_value_store(shell, i);
}
