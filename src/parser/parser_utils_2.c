/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:09:18 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 16:24:48 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Purges redirection tokens from the shell's expand list.
 * Redirection tokens and file names are removed.
 *
 * @param shell The shell structure.
 */
void	purge_redir(t_shell *shell)
{
	t_expand	*current;
	t_expand	*temp;
	t_expand	*ptr;

	current = shell->expand;
	temp = shell->expand;
	while (current != NULL)
	{
		if (current->token == T_PIPE)
			break ;
		if (current->token != T_WORD && current->next->token == T_WORD)
		{
			ptr = current->next;
			if (temp == current || temp == ptr)
			{
				if (ptr->next == NULL)
				{
					delete_node(shell, current);
					delete_node(shell, ptr);
					break;
				}
				temp = ptr->next;
			}
			delete_node(shell, current);
			delete_node(shell, ptr);
			current = temp;
		}
		current = current->next;
	}
}

/**
 * Deletes a node from the expand list in the shell structure
 * at "current" position.
 * 
 * @param shell The shell structure.
 * @param current The node to be deleted.
 */
void	delete_node(t_shell *shell, t_expand *current)
{
	t_expand	*ptr;

	if (shell == NULL || current == NULL)
		return ;
	ptr = shell->expand;
	while (ptr != NULL)
	{
		if (ptr == current)
		{
			if (ptr == shell->expand)
				shell->expand = ptr->next;
			if (ptr->prev != NULL)
				ptr->prev->next = ptr->next;
			if (ptr->next != NULL)
				ptr->next->prev = ptr->prev;
			free(ptr->word);
			free(ptr);
			return ;
		}
		ptr = ptr->next;
	}
}

/**
 * Frees the memory allocated for an array of strings.
 * 
 * @param double_str The array of strings to be freed.
 */
void	free_io(char **double_str)
{
	free(double_str[0]);
	free(double_str[1]);
	free(double_str[2]);
	free(double_str[3]);
	free(double_str);
}

/**
 * Creates a parser node and adds it to the shell's parser.
 * also frees the memory allocated for the arguments, I/O redirections,
 * and files.
 * @param shell The shell structure.
 * @param args An array of arguments.
 * @param io An array of I/O redirections.
 * @param files An array of file names.
 */
void	create_parser_node(t_shell *shell, char **args, char **io, char **files)
{
	t_parser	*element;

	element = parsernew_ms(args, io, files);
	parseraddback_ms(&shell->parser, element);
	free_io(io);
	free_double(files);
	free_double(args);
}

/**
 * Adjusts the output of the parser.
 * If the output is not set, it is set to T_PIPE or O_STDOUT.
 * 
 * @param shell The shell structure.
 */
void	adjust_output(t_shell *shell)
{
	t_parser	*current;

	current = shell->parser;
	while (current->next != NULL)
	{
		if (current->next != NULL && current->o_str == NULL)
		{
			current->output = T_PIPE;
			current->o_str = "PIPE";
		}
		current = current->next;
	}
	if (current->next == NULL && current->o_str == NULL)
	{
		current->output = O_STDOUT;
		current->o_str = "STDOUT";
	}
}
