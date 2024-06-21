/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:35:03 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/21 15:00:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	remove_pipe_on_input(t_shell *shell)
{
	t_exec *exec;
	int		state;
	int		pipe_count;
	
	state = 0;
	pipe_count = 0;
	exec = shell->exec;
	while(exec != NULL)
	{
		if (exec->operator == PIPE)
		{
			pipe_count++;
			state = 1;
		}	
		else if (exec->operator == LESS || exec->operator == HEREDOC)
			state = 2;
		exec = exec->next;
	}
	if (state == 2 || state == 0)
		free_nodes_on_pipe(shell, pipe_count);
}

void free_nodes_on_pipe(t_shell *shell, int pipe_count)
{
	t_exec *exec;
	t_exec *temp;

	exec = shell->exec;
	while (exec->next != NULL && pipe_count > 0)
	{
		if (exec != NULL && exec->operator == PIPE)
			pipe_count--;
		if (pipe_count == 0)
			break;
		temp = exec->next;
		free_double(exec->token);
		free(exec);
		exec = temp;
	}
	if (exec->operator == PIPE)
	{
		temp = exec->next;
		free_double(exec->token);
		free(exec);
		exec = temp;
	}
	shell->exec = exec;
}

void get_token_count(t_shell *shell)
{
	t_exec *exec;

	exec = shell->exec;
	while (exec != NULL)
	{
		exec->token_count = count_dblptr(exec->token);
		exec = exec->next;
	}
}