/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:02:20 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 19:51:10 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Creates and adds a new execution node to the shell's execution list.
 *
 * @param shell The shell structure.
 * @param args The array of arguments for the execution node.
 * @param operand The operator associated with the execution node.
 */
void	create_exec_node(t_shell *shell, char **args, int operand)
{
	t_exec	*node;

	node = (t_exec *)malloc(sizeof(t_exec));
	node->token = double_dup(args);
	node->token_count = 0;
	node->operator = operand;
	node->index = 0;
	node->next = NULL;
	execaddback_ms(&shell->exec, node);
}

/**
 * Frees the memory allocated for a linked list of t_exec structures.
 *
 * @param lst A pointer to the head of the linked list.
 * @return NULL.
 */
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

/**
 * Adds a new t_exec node to the end of the linked list.
 *
 * @param lst The pointer to the head of the linked list.
 * @param new The new t_exec node to be added.
 */
void	execaddback_ms(t_exec **lst, t_exec *new)
{
	t_exec	*temp;

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

/**
 * Removes an execution node at the specified index from the exec list.
 * If the list is empty or the node at the specified index is not found,
 *  an error message is printed.
 *
 * @param shell The shell structure.
 * @param index The index of the execution node to be removed.
 */
void	remove_exec_node_at_index(t_shell *shell, int index)
{
	t_exec	*exec;
	t_exec	*temp;

	if (shell->exec == NULL)
		return ;
	exec = shell->exec;
	if (exec->index == index)
	{
		shell->exec = exec->next;
		free_double(exec->token);
		free(exec);
		return ;
	}
	while (exec->next != NULL && exec->next->index != index)
		exec = exec->next;
	if (exec->next == NULL)
	{
		perror("Node not found");
		return ;
	}
	temp = exec->next;
	exec->next = temp->next;
	free_double(temp->token);
	free(temp);
}
