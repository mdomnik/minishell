/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:56:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 16:11:12 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	adjust_exec_operand(t_shell *shell, int pipe_count)
{
	t_exec	*exec;
	int		temp_operand;

	exec = shell->exec;
	temp_operand = NONE;
	while(pipe_count > 0 && exec->next != NULL)
	{
		if (exec->operator == PIPE)
			pipe_count--;
		exec = exec->next;
	}
	while (exec->next != NULL)
	{
		temp_operand = exec->operator;
		exec->operator = exec->next->operator;
		exec->next->operator = temp_operand;
		exec = exec->next;
	}
	if (shell->expand != NULL)
		exec->operator = PIPE;
	else
		exec->operator = NONE;
}

void set_token_count(t_shell *shell)
{
	t_exec	*exec;
	int		count;

	exec = shell->exec;
	count = 0;
	while (exec != NULL)
	{
		if (exec->token != NULL)
		{
			count = 0;
			while (exec->token[count] != NULL)
				count++;
			exec->token_count = count;
		}
		exec = exec->next;
	}
}