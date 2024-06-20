/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:02:20 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/20 19:43:29 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_exec	*execfreelist_ms(t_exec **lst)
{
	t_exec	*temp;

	temp = *lst;
	if (!(*lst))
		return (NULL);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->token != NULL)
			free_double((*lst)->token);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (NULL);
}

void	execaddback_ms(t_exec **lst, t_exec *new)
{
	t_exec		*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}