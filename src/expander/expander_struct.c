/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:50:12 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/20 20:17:17 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Creates a new expand structure with the given word and token.
 *
 * @param word The word to be stored in the expand structure.
 * @param token The token associated with the word.
 * @return A pointer to the newly created expand structure.
 */
t_expand	*expandnew_ms(char *word, int token)
{
	t_expand	*element;

	element = (t_expand *)malloc(sizeof(t_expand));
	if (!element)
		free_err(ERR_EXPAND, NULL);
	if (word)
	{
		element->word = ft_strdup(word);
		free(word);
	}
	else
		element->word = NULL;
	element->token = token;
	element->index = (reset_increment_j(1) - 1);
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

/**
 * @brief Resets or increments the value of the static variable 'j'.
 *
 * This function is used to reset the value of 'j' to 0 or increment it by 1,
 * depending on the value of the parameter 'x'.
 *
 * @param x The value used to determine whether to reset or increment 'j'.
 * @return The updated value of 'j'.
 */
int	reset_increment_j(int x)
{
	static int	j = 0;

	if (x == 0)
		j = 0;
	else
		j++;
	return (j);
}

/**
 * Adds a new t_expand node to the end of the linked list.
 *
 * @param lst The pointer to the head of the linked list.
 * @param new The pointer to the new t_expand node to be added.
 */
void	expandaddback_ms(t_expand **lst, t_expand *new)
{
	t_expand	*temp;

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
 * Frees the memory allocated for the expand list
 *  and resets the increment_j variable.
 *
 * @param lst The pointer to the expand list.
 * @return NULL.
 */
t_expand	*expandfreelist_ms(t_expand **lst)
{
	t_expand	*temp;

	temp = *lst;
	if (!(*lst))
		free_err(ERR_EXPAND, NULL);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->word)
			free ((*lst)->word);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	reset_increment_j(0);
	return (NULL);
}
