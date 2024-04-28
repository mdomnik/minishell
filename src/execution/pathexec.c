/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:39:10 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/28 21:50:16 by mdomnik          ###   ########.fr       */
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
	char **path;
	int i;

	path = prep_path(shell);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], shell->parser->cmd);
		if (access(path[i], F_OK) == 0)
		{
			shell->parser->args = append_cmd_front(shell, shell->parser->args);
			if (execve(path[i], shell->parser->args, shell->env) == 0)
			{
				printf("cool\n");
			}
			free_double(path);
			printf("efafaefaefaE\n");
			return (0);
		}
		i++;
	}	
	free_double(path);
	return (1);
}