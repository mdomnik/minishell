/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:08:26 by kaan              #+#    #+#             */
/*   Updated: 2024/06/20 15:22:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	redir_check(t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	while (temp->next && temp->operator == NONE)
		temp = temp->next;
	if (temp->operator != NONE && temp->operator != PIPE)
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
