/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:41:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 18:04:16 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_parser	*parsernew_ms(void)
{
	t_parser		*element;
	element = (t_parser *)malloc(sizeof(t_parser));
	if (!element)
		return (NULL);
	// element->
	element->index = (reset_increment_j(1) - 1);
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

int	reset_increment_j(int x)
{
	static int j = 0;
	if (x == 0)
		j = 0;
	else
		j++;
	return (j);
}

// //adds new node to the back of the lexer linked list
// void	lexeraddback_ms(t_lexer **lst, t_lexer *new)
// {
// 	t_lexer		*temp;

// 	temp = *lst;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	while (temp->next != NULL)
// 		temp = temp->next;
// 	temp->next = new;
// 	new->prev = temp;	
// }

// //frees the lexer linked list
// t_lexer *lexerfreelist_ms(t_lexer **lst)
// {
// 	t_lexer *temp;

// 	temp = *lst;
// 	if (!(*lst))
// 		return (NULL);
// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		if ((*lst)->word)
// 			free ((*lst)->word);
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// 	return (NULL);
// }

// void delete_node_at_index(t_lexer **lexer, int index)
// {
// 	t_lexer *current = *lexer;

// 	if (*lexer == NULL)
// 	{
// 		printf("List is empty. Cannot delete.\n");
// 		return;
// 	}
// 	if (index == 0)
// 	{
// 		*lexer = current->next;
// 		if (*lexer != NULL)
// 			(*lexer)->prev = NULL;
// 		free(current);
// 		return;
// 	}
// 	while (current->index != index)
// 		current = current->next;
// 	if (current == NULL) {
// 		printf("Index out of range. Cannot delete.\n");
// 		return;
// 	}
// 	current->prev->next = current->next;
// 	if (current->next != NULL)
// 		current->next->prev = current->prev;
// 	free(current);
// }

// int	reset_increment_i(int x)
// {
// 	static int i = 0;
// 	if (x == 0)
// 		i = 0;
// 	else
// 		i++;
// 	return (i);
// }