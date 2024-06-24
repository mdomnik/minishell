/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:04:13 by kaan              #+#    #+#             */
/*   Updated: 2024/06/24 16:03:14 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_path(t_shell *shell, char **paths, char *cmd, int exit_status_x)
{
	if (cmd)
		perror(cmd);
	if(paths != NULL)
		free_double(paths);
	if (!WIFSIGNALED(exit_status_x))
		*(shell->exit_status) = exit_status_x;
	*(shell->exit_status) = exit_status_x;
	free_shell(shell);
	exit(*(shell->exit_status));
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

char	**append_cmd_front(t_shell *shell, char **args)
{
	char	**copy;
	int	 i;
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
void	exec_external(t_shell *shell, char *path)
{
	shell->exec->token = append_cmd_front(shell, shell->exec->token);
	execve(path, shell->exec->token, shell->env);
}
int ft_exec_external(t_shell *shell, char *cmd, char **path)
{
	exec_external(shell, cmd);
	free_double(path);
	return (0);
}
int find_path(t_shell *shell, t_exec *exec)
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
