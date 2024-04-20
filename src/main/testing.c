/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/20 17:30:02 by mdomnik          ###   ########.fr       */
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
	printf("----------------------\n");
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
	printf("----------------------\n");
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
	printf("----------------------\n");
}

void	test_parser_pointers(char **args, char **io, char **files)
{
	int	i;
	
	i = 0;
	while(files[i] != NULL)
	{
		printf("files[%d]: %s\n", i, files[i]);
		i++;
	}
	i = 0;
	while(args[i] != NULL)
	{
		printf("args[%d]: %s\n", i, args[i]);
		i++;
	}
	printf("io[0]: %s\n", io[0]);
	printf("io[1]: %s\n", io[1]);
	printf("io[2]: %s\n", io[2]);
	printf("io[3]: %s\n", io[3]);
	printf("----------------\n");
}
