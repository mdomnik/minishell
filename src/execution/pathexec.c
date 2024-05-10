/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:39:10 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 17:45:39 by mdomnik          ###   ########.fr       */
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
	if (cmp_str(shell->parser->cmd, "./minishell") == 0)
		printf("raising shlvl\n");
	if (access(shell->parser->cmd, F_OK | X_OK) == 0)
	{
		exec_external(shell, shell->parser->cmd);
		free_double(path);
		return (0);
	}
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], shell->parser->cmd);
		printf("path: %s\n", path[i]);
		if (access(path[i], F_OK | X_OK) == 0)
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

	shell->parser->args = append_cmd_front(shell, shell->parser->args);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, shell->parser->args, shell->env) == -1)
			exit(1);
	}
	wait(NULL);
}
