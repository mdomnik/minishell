/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/17 14:30:04 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//prints the entire stack (linked list)
void	print_lexer(t_shell *shell)
{
	t_lexer	*current;

	current = shell->lexer;
	if (shell->lexer == NULL)
		printf("Stack is empty\n");
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("word: [%s] ", current->word);
		printf("token: [%d] ", current->token);
		printf("join: [%d] ", current->join);
		printf("quote: [%d] ", current->quote);
		printf("index: [%d]\n", current->index);
		current = current->next;
	}
}

//prints the entire stack (linked list)
void	print_expand(t_shell *shell)
{
	t_expand	*current;

	current = shell->expand;
	if (shell->expand == NULL)
		printf("Stack is empty\n");
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("word: [%s] ", current->word);
		printf("token: [%d] ", current->token);
		printf("index: [%d]\n", current->index);
		current = current->next;
	}
}
