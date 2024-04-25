/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:17:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/26 01:06:33 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Changes the current working directory.
 * 
 * @param shell The shell structure.
 */
void	builtin_cd(t_shell *shell)
{
	if (count_args(shell->parser->args) > 2)
	{
		reset_loop(shell, ERR_ARG);
		return ;
	}
	else if (count_args(shell->parser->args) == 0)
	{
		if (chdir(getenv("HOME")) == -1)
		{
			printf("minishell: cd: %s:", getenv("HOME"));
			reset_loop(shell, ERR_CD);
			return ;
		}
		reset_loop(shell, NULL);
		return ;
	}
	else if (chdir(shell->parser->args[0]) == -1)
	{
		printf("minishell: cd: %s:", shell->parser->args[0]);
		reset_loop(shell, ERR_CD);
		return ;
	}
	reset_loop(shell, NULL);
}
