/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:10:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 16:37:31 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

//creates a new node in the lexer linked list
t_lexer	*lexernew_ms(char *word, t_tokens token)
{
	t_lexer		*element;
	element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!element)
		return (NULL);
	element->word = ft_strdup(word);
	element->token = token;
	element->index = (reset_increment_i(1) - 1);
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

//adds new node to the back of the lexer linked list
void	lexeraddback_ms(t_lexer **lst, t_lexer *new)
{
	t_lexer		*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;	
}

//frees the lexer linked list
t_lexer *lexerfreelist_ms(t_lexer **lst)
{
	t_lexer *temp;

	temp = *lst;
	if (!(*lst))
		return (NULL);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->word)
			free ((*lst)->word);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (NULL);
}

void delete_node_at_index(t_lexer **lexer, int index)
{
	t_lexer *current = *lexer;

	if (*lexer == NULL)
	{
		printf("List is empty. Cannot delete.\n");
		return;
	}
	if (index == 0)
	{
		*lexer = current->next;
		if (*lexer != NULL)
			(*lexer)->prev = NULL;
		free(current);
		return;
	}
	while (current->index != index)
		current = current->next;
	if (current == NULL) {
		printf("Index out of range. Cannot delete.\n");
		return;
	}
	current->prev->next = current->next;
	if (current->next != NULL)
		current->next->prev = current->prev;
	free(current);
}

int	reset_increment_i(int x)
{
	static int i = 0;
	if (x == 0)
		i = 0;
	else
		i++;
	return (i);
}