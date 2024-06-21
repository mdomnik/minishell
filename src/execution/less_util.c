/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:52:14 by kaan              #+#    #+#             */
/*   Updated: 2024/06/21 15:12:33 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	less_nofile_exit(void)
{
	ft_putendl_fd(NO_FILE, STDERR_FILENO);
	//exit(EXIT_FAILURE);
}

void	less_multi_file(t_exec *exec, int fd)
{
	int	i;

	i = 1;
	while (exec->token[i]
		&& access(exec->token[i], F_OK) == 0)
	{
		fd = open(exec->token[i], O_RDONLY, 0666);
		dup2(fd, STDIN_FILENO);
		i++;
	}
}

void	less_one_file(t_exec *exec, int fd)
{
	fd = open(exec->token[0], O_RDONLY, 0666);
	dup2(fd, STDIN_FILENO);
}

void	less_invalid_input(char *token)
{
	char	*err_msg;

	err_msg = ft_strjoin("minishell: ", token);
	perror(err_msg);
	free(err_msg);
	exit_status = 2;
	exit(EXIT_FAILURE);
}
