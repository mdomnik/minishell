/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:17:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/25 23:51:32 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_cd(t_shell *shell)
{
	if (count_args(shell->parser->args) > 2)
	{
		reset_loop(shell, ERR_ARG);
		return ;
	}
	if (chdir(shell->parser->args[0]) == -1)
	{
		printf("minishell: cd: %s:", shell->parser->args[0]);
		reset_loop(shell, ERR_CD);
		return ;
	}
	reset_loop(shell, NULL);
}
