/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:28:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 16:31:53 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_shell *shell)
{
	group_redir(shell);
	adjust_output(shell);
	execute(shell);
}

/**
 * Handles grouping and redirection in the shell.
 *
 * This function processes the tokens in the shell's expansion list and performs
 * grouping and redirection operations based on the token types. It checks for
 * syntax errors and populates the `io` array with input/output file names.
 * The `file_num` variable keeps track of the number of files in the `io` array.
 *
 * @param shell A pointer to the shell structure.
 */
void	group_redir(t_shell *shell)
{
	t_expand	*cur;
	char		**io;
	int			file_num;

	cur = shell->expand;
	if (!cur)
		return ;
	io = (char **)ft_calloc(4, sizeof(char *));
	file_num = 0;
	while (cur->next != NULL)
	{
		if ((cur->token != T_WORD && cur->token != T_PIPE) 
				&& (cur->next->token != T_WORD || !cur->next))
		{
			free_double(io);
			reset_loop(shell, ERR_SYNTAX);
		}
		if (cur->token == T_PIPE)
			break ;
		if (cur->token != T_WORD && cur->next->token == T_WORD)
		{
			if (cur->token == T_PIPE)
				break ;
			else
				handle_token(cur, io, &file_num);
		}
		cur = cur->next;
	}
	if (cur->token != T_WORD && cur->token != T_PIPE)
	{
		free_double(io);
		reset_loop(shell, ERR_SYNTAX);
	}
	group_files(shell, io, file_num);
}

/**
 * Groups files and passes them to the `group_args` function.
 *
 * This function takes a `t_shell` struct, an array of input/output redirection
 * strings (`io`), and the number of files (`file_num`). It groups the files
 * from the `t_expand` linked list in the `shell` struct and stores them in the
 * `files` array. Then, it calls the `group_args` function to process the
 * grouped arguments.
 *
 * @param shell     The `t_shell` struct containing the expand linked list.
 * @param io        An array of input/output redirection strings.
 * @param file_num  The number of files to be grouped.
 */
void	group_files(t_shell *shell, char **io, int file_num)
{
	t_expand	*current;
	char		**files;

	current = shell->expand;
	if (!current)
		return ;
	files = (char **)ft_calloc((file_num + 1), sizeof(char *));
	file_num = 0;
	while (current->next != NULL)
	{
		if (current->token == T_PIPE)
			break ;
		if (current->token != T_WORD && current->next->token == T_WORD)
		{
			if (current->token == T_PIPE)
				break ;
			else if (current->token == T_GREATER || current->token == T_APPEND)
				files[file_num++] = ft_strdup(current->next->word);
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	purge_redir(shell);
	group_args(shell, io, files);
}

/**
 * Groups arguments from the shell's expand list and creates a parser node.
 * 
 * @param shell The shell structure.
 * @param io An array of input/output redirections.
 * @param files An array of file names for redirections.
 */
void	group_args(t_shell *shell, char **io, char **files)
{
	char		**args;
	t_expand	*current;
	int			arg_num;

	current = shell->expand;
	arg_num = count_args_before_pipe(current);
	args = (char **)ft_calloc((arg_num + 1), sizeof(char *));
	if (!args)
		free_err(ERR_MALLOC, shell);
	arg_num = 0;
	current = shell->expand;
	while (current != NULL)
	{
		if (current->token == T_PIPE)
			break ;
		args[arg_num++] = ft_strdup(current->word);
		delete_node(shell, current);
		current = shell->expand;
	}
	create_parser_node(shell, args, io, files);
	if (current != NULL)
	{
		delete_node(shell, current);
		group_redir(shell);
	}
}
