/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:39:10 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/04 17:38:25 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**prep_path(t_shell *shell)
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
		reset_loop(shell, ERR_PATH, shell->parser->cmd, 1);
	}
	free(env);
	return (path);
}

int	ft_exec_external(t_shell *shell, char *cmd, char **path)
{
	exec_external(shell, cmd);
	free_double(path);
	return (0);
}

int	path_validation(t_shell *shell, char **path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], shell->parser->cmd);
		if (access(path[i], F_OK | X_OK) == 0)
			return (ft_exec_external(shell, path[i], path));
		i++;
	}
	return (-1);
}

int	find_path(t_shell *shell)
{
	char	**path;

	path = prep_path(shell);
	if (cmp_str(shell->parser->cmd, "./minishell") == 0)
		raise_shlvl(shell);
	if (access(shell->parser->cmd, F_OK | X_OK) == 0)
		return (ft_exec_external(shell, shell->parser->cmd, path));
	if (path_validation(shell, path) == -1)
	{
		reset_loop(shell, ERR_CMD, shell->parser->cmd, 1);
		free_double(path);
	}
	return (1);
}

void	exec_external(t_shell *shell, char *path)
{
	shell->parser->args = append_cmd_front(shell, shell->parser->args);
	execve(path, shell->parser->args, shell->env);
}
