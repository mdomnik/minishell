/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:17:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/25 13:57:14 by mdomnik          ###   ########.fr       */
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
	char	*oldpwd;
	char	*newpwd;
	int		i;

	i = check_argument_count(shell, exec);
	if (i == -1)
		return (-1);
	if (i == 0)
		return (0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(exec->token[1]) == -1)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		return (-1);
	}
	else
	{
		newpwd = getcwd(NULL, 0);
		update_pwd_oldpwd(shell, ft_strdup(newpwd), ft_strdup(oldpwd));
		free(newpwd);
	}
	free(oldpwd);
	return (0);
}

int	check_argument_count(t_shell *shell, t_exec *exec)
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
	return (1);
}

int	cd_home(t_shell *shell)
{
	char	*home;
	char	*oldpwd;

	home = ft_getenv("HOME", shell->env);
	oldpwd = getcwd(NULL, 0);
	if (!home)
	{
		return (-1);
	}
	if (chdir(home) == -1)
	{
		free(home);
		return (-1);
	}
	update_pwd_oldpwd(shell, home, oldpwd);
	return (0);
}

void	change_last_dir(t_shell *shell)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = ft_getenv("OLDPWD", shell->env);
	newpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return ;
	}
	if (!newpwd)
	{
		ft_putendl_fd("cd: PWD not set", 2);
		return ;
	}
	if (chdir(oldpwd) == -1)
	{
		ft_putendl_fd("cd: No such file or directory", 2);
		return ;
	}
	printf("%s\n", oldpwd);
	update_pwd_oldpwd(shell, oldpwd, newpwd);
}
