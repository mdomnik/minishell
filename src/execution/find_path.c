/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:04:13 by kaan              #+#    #+#             */
/*   Updated: 2024/06/21 14:35:42 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	exit_path(t_shell *shell, char **paths, char *cmd, int exit_status_x)
{
	if (cmd)
		perror(cmd);
	if(paths != NULL)
		free_double(paths);
	if (!WIFSIGNALED(exit_status_x))
		(exit_status) = exit_status_x;
	free_shell(shell);
	exit(exit_status);
}

char	**get_paths(t_shell *shell)
{
	char	**path;
	char	*env;
	char	*tmp;

	tmp = ft_getenv("PATH", shell->env);
	env = ft_strdup(tmp);
	if (tmp)
		free(tmp);
	path = ft_split_ms(env, ':');
	if (!path)
	{
		free(env);
		free_double(path);
		exit(127);
	}
	free(env);
	return (path);
}

char	*get_bin_path(char *cmd, char **paths)
{
	size_t	i;
	char	*bin_path;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin_msn(paths[i], cmd);
		if (access(paths[i], F_OK | X_OK) == 0)
		{
			bin_path = ft_strdup(paths[i]);
			return (bin_path);
		}
		i++;
	}
	return (NULL);
}

void	err_cmd(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	find_path(t_shell *shell, t_exec *exec)
{
	char		*bin_path;
	char		**paths;

	bin_path = exec->token[0];
	paths = get_paths(shell);
	if (!paths)
		exit(127);
	bin_path = get_bin_path(exec->token[0], paths);
	if (!bin_path)
	{
		err_cmd(exec->token[0]);
		exit_path(shell, paths, NULL, 127);
	}
	if (execve(bin_path, exec->token, shell->env) == -1)
	{
		free(bin_path);
		exit_path(shell, paths, exec->token[0], 127);
	}
	return ;
}
