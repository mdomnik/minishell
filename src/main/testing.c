/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/18 14:45:31 by mdomnik          ###   ########.fr       */
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

//prints the entire stack (linked list)
void	print_parser(t_shell *shell)
{
	t_parser	*current;
	int			i;

	current = shell->parser;
	if (shell->parser == NULL)
		printf("Stack is empty\n");
	printf("parser contents:\n");
	while (current != NULL)
	{
		printf("cmd: [%s] ", current->cmd);
		printf("args: ");
		i = 0;
		while (current->args[i] != NULL)
		{
			printf("[%s] ", current->args[i]);
			i++;
		}
		printf("\n");
		printf("input: [%d] [%s]\n", current->input, current->i_str);
		printf("output: [%d] [%s]\n", current->output, current->o_str);
		printf("files: ");
		i = 0;
		while (current->files[i] != NULL)
		{
			printf("[%s] ", current->files[i]);
			i++;
		}
		printf("\n");
		printf("index: %d\n", current->index);
		current = current->next;
	}
}
