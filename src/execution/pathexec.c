/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:39:10 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/03 14:38:07 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**prep_path(t_shell *shell)
{
	char	**path;
	char	*env;

	env = ft_strdup(getenv("PATH"));
	path = ft_split_ms(env, ':');
	if (!path)
	{
		free(env);
		free_double(path);
		reset_loop(shell, ERR_PATH);
	}
	free(env);
	return (path);
}

int	find_path(t_shell *shell)
{
	char	**path;
	int		i;

	path = prep_path(shell);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		if (shell->parser->cmd[0] == '.' && shell->parser->cmd[1] == '/')
			path[i] = ft_strjoin(path[i], "./");
		else
			path[i] = ft_strjoin(path[i], shell->parser->cmd);
		if (access(path[i], F_OK) == 0)
		{
			exec_external(shell, path[i]);
			free_double(path);
			return (0);
		}
		i++;
	}
	free_double(path);
	return (1);
}

void	exec_external(t_shell *shell, char *path)
{
	pid_t	pid;

	pid = fork();
	shell->parser->args = append_cmd_front(shell, shell->parser->args);
	if (pid == 0)
		execve(path, shell->parser->args, shell->env);
	wait(NULL);
}