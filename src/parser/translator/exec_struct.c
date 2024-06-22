/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:02:20 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 15:41:05 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	create_exec_node(t_shell *shell, char **args, int operand)
{
	t_exec	*node;
	int		i;

	i = 0;
	node = (t_exec *)malloc(sizeof(t_exec));
	node->token = double_dup(args);
	node->token_count = 0;
	node->operator = operand;
	node->next = NULL;
	execaddback_ms(&shell->exec, node);
}

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

t_expand *remove_current_node(t_expand *expand)
{
	t_expand	*next;
	t_expand	*prev;
	
	next = expand->next;
	prev = expand->prev;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	free(expand->word);
	free(expand);
	return (next);
}