/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:59:48 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 19:25:15 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints the current working directory.
 *
 * @param shell The shell structure.
 */
void	builtin_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		reset_loop(shell, ERR_PWD);
	printf("%s\n", pwd);
	update_pwd_env_declare(shell, pwd);
	free(pwd);
	reset_loop(shell, NULL);
}

void	update_pwd_env_declare(t_shell *shell, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("PWD=");
	while(shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(tmp, str);
			break ;
		}
		i++;
	}
	i = 0;
	tmp = ft_strdup("PWD=");
	while(shell->declare[i])
	{
		if (ft_strncmp(shell->declare[i], "PWD=", 4) == 0)
		{
			free(shell->declare[i]);
			shell->declare[i] = ft_strjoin(tmp, str);
			break ;
		}
		i++;
	}
}
