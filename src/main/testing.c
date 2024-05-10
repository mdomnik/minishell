/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 16:39:15 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TO DELETE LATER

/**
 * Prints the contents of the lexer stack.
 * 
 * @param shell The shell structure containing the lexer stack.
 */
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

/**
 * Prints the contents of the expand stack in the given shell.
 *
 * @param shell The shell containing the expand stack.
 */
void	print_expand(t_shell *shell)
{
	t_expand	*current;

	current = shell->expand;
	if (shell->expand == NULL)
		printf("Stack is empty\n");
	printf("expander Stack contents:\n");
	while (current != NULL)
	{
		printf("word: [%s] ", current->word);
		printf("token: [%d] ", current->token);
		printf("index: [%d]\n", current->index);
		current = current->next;
	}
	printf("----------------------\n");
}

/**
 * Prints the contents of the parser in the given shell.
 *
 * @param shell The shell containing the parser.
 */
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
		if (current->args != NULL)
		{
			while (current->args[i] != NULL)
			{
				printf("[%s] ", current->args[i]);
				i++;
			}		
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

/**
 * This function is used to test the pointers in the parser.
 * It takes three arrays of strings as arguments: args, io, and files.
 * It prints the values of the files array, args array, and io array.
 * 
 * @param args   The array of strings representing command arguments.
 * @param io     The array of strings representing input/output redirection.
 * @param files  The array of strings representing file names.
 */
void	test_parser_pointers(char **args, char **io, char **files)
{
	int	i;

	i = 0;
	while (files[i] != NULL)
	{
		printf("files[%d]: %s\n", i, files[i]);
		i++;
	}
	i = 0;
	while (args[i] != NULL)
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
