/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 15:21:52 by mdomnik          ###   ########.fr       */
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
		i = 0;
		printf("file_types: ");
		while (current->file_types[i] != 0)
		{
			printf("[%d] ", current->file_types[i]);
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

void print_exec(t_shell *shell)
{
	t_exec	*current;
	int	i;

	i = 0;
	current = shell->exec;
	if (shell->exec == NULL)
		printf("Stack is empty\n");
	printf("exec Stack contents:\n");
	while (current != NULL)
	{
		printf("tokens :");
		i = 0;
		while (current->token[i] != NULL)
		{
			printf(" %s", current->token[i]);
			i++;
		}
		if (current->operator == NONE)
			printf(" [NONE]");
		else if (current->operator == GREAT)
			printf(" [GREAT]");
		else if (current->operator == APPEND)
			printf(" [APPEND]");
		else if (current->operator == LESS)
			printf(" [LESS]");
		else if (current->operator == HEREDOC)
			printf(" [HEREDOC]");
		else if (current->operator == PIPE)
			printf(" [PIPE]");
		printf(" [TC: %d]\n", current->token_count);
		current = current->next;
	}
	printf("----------------------\n");
}

void print_double_pointer(char **list)
{
	int	i;

	i = 0;
	printf("Printing double pointer\n");
	while (list[i] != NULL)
	{
		printf("list[%d]: %s\n", i, list[i]);
		i++;
	}
	printf("----------------\n");
}

void print_triple_pointer(char ***triple_pointer)
{
	int i;
	int j;

	i = 0;
	printf("Printing triple pointer\n");
	while (triple_pointer[i] != NULL)
	{
		j = 0;
		while (triple_pointer[i][j] != NULL)
		{
			printf("%s ", triple_pointer[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}