/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:59:53 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 18:00:20 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_external(t_shell *shell, char *path)
{
	shell->exec->token = append_cmd_front(shell, shell->exec->token);
	execve(path, shell->exec->token, shell->env);
}

int	ft_exec_external(t_shell *shell, char *cmd, char **path)
{
	exec_external(shell, cmd);
	free_double(path);
	return (0);
}

int	find_path(t_shell *shell, t_exec *exec)
{
	char		*bin_path;
	char		**paths;

	bin_path = exec->token[0];
	paths = get_paths(shell);
	if (!paths)
		exit(127);
	if (access(exec->token[0], F_OK | X_OK) == 0)
		return (ft_exec_external(shell, exec->token[0], paths));
	bin_path = get_bin_path(exec->token[0], paths);
	if (!bin_path)
	{
		perror("empty bin path");
		err_cmd(exec->token[0]);
		exit_path(shell, paths, NULL, 1);
	}
	if (execve(bin_path, exec->token, shell->env) == -1)
	{
		free(bin_path);
		exit_path(shell, paths, exec->token[0], 127);
	}
	return (0);
}
