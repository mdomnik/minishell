/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:09:18 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/19 15:25:56 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void purge_redir(t_shell *shell)
{
	t_expand *current;

	current = shell->expand;
	while (current != NULL)
	{
		if (current->token == T_PIPE)
			break ;
		if (current->token != T_WORD && current->next->token == T_WORD)
		{
			delete_node(shell, current);
			current = current->next;
			delete_node(shell, current);
		}
		current = current->next;
	}	
}

void delete_node(t_shell *shell, t_expand *current)
{
	t_expand *ptr;

    if (shell == NULL || current == NULL)
        return;
    ptr = shell->expand;
    while (ptr != NULL)
	{
        if (ptr == current)
		{
            if (ptr == shell->expand)
                shell->expand = ptr->next;
            if (ptr->prev != NULL) 
                ptr->prev->next = ptr->next;
            if (ptr->next != NULL) 
                ptr->next->prev = ptr->prev;
            free(ptr->word);
            free(ptr);
            return ;
        }
        ptr = ptr->next;
    }
}