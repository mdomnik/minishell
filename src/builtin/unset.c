/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:35:04 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/20 16:35:31 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_unset(t_shell *shell, t_exec *exec)
{
	int	i;

	i = 1;
	while (exec->token[i])
	{
		unset_declare(shell, exec->token[i]);
		unset_env(shell, exec->token[i]);
		i++;
	}
	sort_declare(shell);
	return (0);
}

void	unset_declare(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (shell->declare[i])
	{
		if (ft_strncmp(str, shell->declare[i], ft_strlen(str)) == 0)
		{
			free(shell->declare[i]);
			while (shell->declare[i + 1])
			{
				shell->declare[i] = shell->declare[i + 1];
				i++;
			}
			shell->declare[i] = NULL;
			return ;
		}
		i++;
	}
}

void	unset_env(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(str, shell->env[i], ft_strlen(str)) == 0)
		{
			free(shell->env[i]);
			while (shell->env[i + 1])
			{
				shell->env[i] = shell->env[i + 1];
				i++;
			}
			shell->env[i] = NULL;
			return ;
		}
		i++;
	}
}
