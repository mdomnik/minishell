/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:37:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 16:54:20 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser	*parsernew_ms(char **args, char **io, char **files)
{
	t_parser		*element;

	element = (t_parser *)malloc(sizeof(t_parser));
	if (!element)
		return (NULL);
	element->index = (reset_increment_k(1) - 1);
	if (args[0] != NULL)
		element->cmd = ft_strdup(args[0]);
	else
		element->cmd = NULL;
	element->args = remove_first(args);
	set_io(io, element);
	element->files = double_dup(files);
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

/**
 * @brief Resets or increments the value of the static variable k.
 *
 * This function is used to reset the value of k to 0 or increment it by 1,
 * depending on the value of the parameter x.
 *
 * @param x The value used to determine whether to reset or increment k.
 * @return The updated value of k.
 */
int	reset_increment_k(int x)
{
	static int	k = 0;

	if (x == 0)
		k = 0;
	else
		k++;
	return (k);
}

/**
 * Adds a new t_parser node to the end of the linked list.
 *
 * @param lst The pointer to the head of the linked list.
 * @param new The pointer to the new t_parser node to be added.
 */
void	parseraddback_ms(t_parser **lst, t_parser *new)
{
	t_parser		*temp;

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
 * Frees the memory allocated for the parser list.
 *
 * @param lst The pointer to the head of the linked list.
 * @return NULL.
 */
t_parser	*parserfreelist_ms(t_parser **lst)
{
	t_parser	*temp;

	temp = *lst;
	if (!(*lst))
		return (NULL);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd)
			free ((*lst)->cmd);
		if ((*lst)->args != NULL)
			free_double((*lst)->args);
		if ((*lst)->files != NULL)
			free_double((*lst)->files);
		if (ft_memcmp_ms((*lst)->i_str, "STDIN") 
			&& ft_memcmp_ms((*lst)->i_str, "PIPE") && (*lst)->i_str != NULL)
			free((*lst)->i_str);
		if (ft_memcmp_ms((*lst)->o_str, "STDOUT") 
			&& ft_memcmp_ms((*lst)->o_str, "PIPE") && (*lst)->o_str != NULL)
			free((*lst)->o_str);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (NULL);
}
