/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:02:20 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 21:55:18 by kaan             ###   ########.fr       */
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
	node->index = 0;
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

void remove_exec_node_at_index(t_shell *shell, int index)
{
    t_exec *exec;
    t_exec *temp;
    // Check if the list is empty
    if (shell->exec == NULL)
    {
        perror("List is empty");
        return;
    }
    exec = shell->exec;
    // If the node to remove is the first node
    if (exec->index == index)
    {
        shell->exec = exec->next;
        free_double(exec->token);
        free(exec);
        print_exec(shell);
        return;
    }
    // Iterate to find the node just before the one to remove
    while (exec->next != NULL && exec->next->index != index)
        exec = exec->next;
    if (exec->next == NULL)
    {
        // Node with the given index was not found
        perror("Node not found");
        return;
    }
    // Remove the node
    temp = exec->next;
    exec->next = temp->next;
    free_double(temp->token);
    free(temp);
    //print_exec(shell);
}