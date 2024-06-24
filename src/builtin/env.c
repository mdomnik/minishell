/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:38:32 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 17:35:49 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints the environment variables stored in the shell.
 *
 * @param shell The shell structure containing the environment variables.
 */
int	builtin_env(t_shell *shell, t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->token[0])
		return (-1);
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
