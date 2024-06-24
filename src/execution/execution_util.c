/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:08:26 by kaan              #+#    #+#             */
/*   Updated: 2024/06/24 20:45:56 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	input_redir_check(t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	while (temp->next && temp->operator == NONE)
		temp = temp->next;
	perror(temp->token[0]);
	if (temp->operator == LESS)
		return (true);
	return (false);
}

bool	pipe_check(t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	while (temp->next && temp->operator == NONE)
		temp = temp->next;
	if (temp->operator == PIPE)
		return (true);
	return (false);
}

bool	is_valid_id(char *token)
{
	size_t	i;

	i = 0;
	if (strcmp_msn(token, "="))
		return (false);
	while (token[i] && token[i] != '=')
	{
		if (ft_isdigit(token[i]) || token[i] == '!' || token[i] == '@'
			|| token[i] == '{' || token[i] == '}' || token[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

void	redir_output(t_shell *shell, t_exec *exec)
{
	close(STDOUT_FILENO);
	remove_output_node(shell, exec);
	if (exec->operator == GREAT)
	{
		ft_open(exec->next->token[0], O_TRUNC);
		exec->operator = exec->next->operator;
		remove_exec_node_at_index(shell, exec->next->index);
	}
	else if (exec->operator == APPEND)
	{
		ft_open(exec->next->token[0], O_APPEND);
		exec->operator = exec->next->operator;
		remove_exec_node_at_index(shell, exec->next->index);
	}
}
