/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:48:02 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/30 18:10:30 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Creates a new lexer element with the given word,
 * token, and join value.
 *
 * @param word The word to be stored in the lexer element.
 * @param token The token associated with the word.
 * @param join The join value indicating whether the word 
 * should be joined with the previous element.
 * @return A pointer to the newly created lexer element.
 */
t_lexer	*lexernew_ms(char *word, t_tokens token, int join, int quote)
{
	t_lexer	*element;

	element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!element)
		free_err(ERR_LEXER, NULL);
	if (word)
	{
		element->word = ft_strdup(word);
		free(word);
	}
	else
		element->word = NULL;
	element->join = join;
	element->token = token;
	element->quote = quote;
	element->index = (reset_increment_i(1) - 1);
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

/**
 * @brief Resets or increments the value of a static variable 'i'.
 *
 * This function is used to reset the value of 'i' to 0 or increment it by 1,
 * depending on the value of the parameter 'x'.
 *
 * @param x The value to determine whether to reset or increment 'i'.
 * @return The updated value of 'i'.
 */
int	reset_increment_i(int x)
{
	static int	i = 0;

	if (x == 0)
		i = 0;
	else
		i++;
	return (i);
}

/**
 * Adds a new lexer node to the end of the linked list.
 *
 * @param lst The pointer to the head of the linked list.
 * @param new The new lexer node to be added.
 */
void	lexeraddback_ms(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

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

/**
 * Frees the memory allocated for a linked list of lexer tokens.
 *
 * @param lst A pointer to the head of the lexer token linked list.
 * @return NULL.
 */
t_lexer	*lexerfreelist_ms(t_lexer **lst)
{
	t_lexer	*temp;

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
	reset_increment_i(0);
	return (NULL);
}

/**
 * Deletes empty nodes from the lexer linked list.
 * 
 * @param shell The shell structure containing the lexer linked list.
 */
void	delete_empty_nodes(t_shell *shell)
{
	t_lexer	*current;
	t_lexer	*temp;

	current = shell->lexer;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		if (temp->word != NULL && temp->word[0] == '\0')
		{
			if (temp->prev != NULL)
				temp->prev->next = temp->next;
			if (temp->next != NULL)
				temp->next->prev = temp->prev;
			free(temp->word);
			free(temp);
		}
	}
}
