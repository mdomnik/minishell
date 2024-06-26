/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:04:13 by kaan              #+#    #+#             */
/*   Updated: 2024/06/26 13:31:05 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_path(t_shell *shell, char **paths, char *cmd, int exit_status_x)
{
	if (cmd)
		perror(cmd);
	if (paths != NULL)
		free_double(paths);
	free_shell(shell);
	exit(exit_status_x);
}

char	**get_paths(t_shell *shell)
{
	char	**path;
	char	*env;
	char	*tmp;

	tmp = ft_getenv("PATH", shell->env);
	if (!tmp)
	{
		free_shell(shell);
		exit(127);
	}
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

char	**append_cmd_front(t_shell *shell, char **args)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (count_args(args) + 2));
	if (!copy)
		return (NULL);
	copy[0] = ft_strdup(shell->exec->token[0]);
	while (args[i] != NULL)
	{
		copy[i + 1] = ft_strdup(args[i]);
		if (!copy[i])
		{
			free_double(copy);
			return (NULL);
		}
		i++;
	}
	copy[i + 1] = NULL;
	free_double(args);
	return (copy);
}
