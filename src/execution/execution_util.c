/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:08:26 by kaan              #+#    #+#             */
/*   Updated: 2024/06/22 20:23:13 by kaan             ###   ########.fr       */
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
