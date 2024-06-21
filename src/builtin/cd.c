/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:17:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/21 14:21:43 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Changes the current working directory.
 * 
 * @param shell The shell structure.
 */
int	builtin_cd(t_shell *shell, t_exec *exec)
{
	if (exec->token_count > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (-1);
	}
	else if (exec->token_count == 1)
	{
		cd_home(shell);
		return (0);
	}
	else if (cmp_str(exec->token[1], "-") == 0)
	{
		change_last_dir(shell);
		return (0);
	}
	set_last_dir(shell);
	if (chdir(exec->token[1]) == -1)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		return (-1);
	}
	return (0);
}

int	cd_home(t_shell *shell)
{
	char	*home;

	home = ft_getenv("HOME", shell->env);
	if (!home)
	{
		return (-1);
	}
	if (chdir(home) == -1)
	{
		free(home);
		return (-1);
	}
	free(home);
	return (0);
}

void	set_last_dir(t_shell *shell)
{
	if (shell->last_dir)
		free(shell->last_dir);
	shell->last_dir = getcwd(NULL, 0);
}

void	change_last_dir(t_shell *shell)
{
	char	*temp;

	printf("%s\n", shell->last_dir);
	temp = getcwd(NULL, 0);
	chdir(shell->last_dir);
	free(shell->last_dir);
	shell->last_dir = ft_strdup(temp);
	free(temp);
}
