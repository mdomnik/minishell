/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:52:14 by kaan              #+#    #+#             */
/*   Updated: 2024/06/22 17:39:41 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	less_nofile(char *token)
{
	int	fd;

	fd = open(token, O_RDONLY, 0666);
	ft_putendl_fd(NO_FILE, fd);
	dup2(fd, STDIN_FILENO);
}

void	less_nopermit_exit(t_shell *shell)
{
	ft_putendl_fd(NO_PERMIT, STDERR_FILENO);
	destroy(shell);
	exit(EXIT_FAILURE);
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

void	less_one_file(t_shell *shell, t_exec *exec, int fd)
{
	fd = open(exec->token[0], O_RDONLY, 0666);
	if (access(exec->token[0], F_OK) == -1)
		ft_putendl_fd(NO_FILE, fd);
	else if (access(exec->token[0], R_OK) == -1)
		less_nopermit_exit(shell);
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
