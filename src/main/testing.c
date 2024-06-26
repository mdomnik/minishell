/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/26 12:49:42 by mdomnik          ###   ########.fr       */
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

void	print_exec(t_shell *shell)
{
	t_exec	*current;
	int		i;

	i = 0;
	current = shell->exec;
	if (shell->exec == NULL)
		ft_putstr_fd("Stack is empty\n", 2);
	ft_putstr_fd("exec Stack contents:\n", 2);
	while (current != NULL)
	{
		ft_putstr_fd("tokens :", 2);
		i = 0;
		while (current->token[i] != NULL)
		{
			ft_putstr_fd(current->token[i], 2);
			ft_putstr_fd(" ", 2);
			i++;
		}
		if (current->operator == NONE)
			ft_putstr_fd(" [NONE]", 2);
		else if (current->operator == GREAT)
			ft_putstr_fd(" [GREAT]", 2);
		else if (current->operator == APPEND)
			ft_putstr_fd(" [APPEND]", 2);
		else if (current->operator == LESS)
			ft_putstr_fd(" [LESS]", 2);
		else if (current->operator == HEREDOC)
			ft_putstr_fd(" [HEREDOC]", 2);
		else if (current->operator == PIPE)
			ft_putstr_fd(" [PIPE]", 2);
		ft_putstr_fd(" [index: ", 2);
		ft_putnbr_fd(current->index, 2);
		ft_putstr_fd("] ", 2);
		ft_putstr_fd(" [TC: ", 2);
		ft_putnbr_fd(current->token_count, 2);
		ft_putstr_fd("]\n", 2);
		current = current->next;
	}
	ft_putstr_fd("----------------------\n", 2);
}

void	print_double_pointer(char **list)
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

void	print_triple_pointer(char ***triple_pointer)
{
	int	i;
	int	j;

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
