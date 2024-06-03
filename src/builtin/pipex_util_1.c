/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:54:29 by kaan              #+#    #+#             */
/*   Updated: 2024/06/02 15:54:54 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	err_fd(void)
{
	perror("Open Error");
	exit(EXIT_FAILURE);
}

void	fd_close(t_shell *shell)
{
	int	i;

	i = 0;
	if (*(shell->fd) != -2)
	{
		while (i != (*(shell->cmd_count) - 1) * 2)
		{
			if (close(shell->fd[i]) == -1)
				perror("fd close error");
			i++;
		}
	}
	if (*(shell->red_fd) != -2)
	{
		if (close(*(shell->red_fd)) == -1)
			perror("red_fd close error");
	}
}
