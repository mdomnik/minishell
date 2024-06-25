/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:28:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/25 19:43:03 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Parses the input shell command and performs necessary transformations.
 * changes it to the desired format for execution.
 * 
 * @param shell The shell structure containing the command and its components.
 */
void	parser(t_shell *shell)
{
	t_expand	*expand;
	int			i;

	i = 0;
	expand = shell->expand;
	while (expand != NULL)
	{
		create_cmd_node(shell, expand);
		create_output_node(shell, expand);
		create_input_node(shell, expand);
		remove_nodes_till_pipe(shell);
		adjust_exec_operand(shell, i);
		i++;
		expand = shell->expand;
	}
	set_token_count(shell);
	set_index_exec(shell);
	execution(shell);
}

/**
 * Creates a command node in the exec's data structure.
 * 
 * @param shell The shell structure.
 * @param expand The expand structure containing the parsed tokens.
 */
void	create_cmd_node(t_shell *shell, t_expand *expand)
{
	char	**args;
	int		i;

	i = count_args_cmd(expand);
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	expand = shell->expand;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_WORD && (expand->prev == NULL
				|| expand->prev->token == T_WORD))
		{
			args[i] = ft_strdup(expand->word);
			i++;
		}
		expand = expand->next;
	}
	args[i] = NULL;
	create_exec_node(shell, args, NONE);
	free_double(args);
}

int	count_args_cmd(t_expand *expand)
{
	int	i;

	i = 0;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_WORD && (expand->prev == NULL
				|| expand->prev->token == T_WORD))
			i++;
		expand = expand->next;
	}
	return (i);
}

/**
 * Creates input nodes in the exec's data structure until
 * end of expand list or pipe.
 * @param shell The shell structure.
 * @param expand The expand linked list.
 */
void	create_input_node(t_shell *shell, t_expand *expand)
{
	t_expand	*temp;

	temp = expand;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_LESSER)
			create_redir_node(shell, expand->next->word, LESS);
		else if (expand->token == T_HEREDOC)
			create_redir_node(shell, expand->next->word, HEREDOC);
		expand = expand->next;
	}
}

/*
 * Creates output nodes in the exec's data structure until
 * end of expand list or pipe.
 * @param shell The shell structure.
 * @param expand The expand linked list.
 */
void	create_output_node(t_shell *shell, t_expand *expand)
{
	t_expand	*temp;

	temp = expand;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_GREATER)
			create_redir_node(shell, expand->next->word, GREAT);
		if (expand->token == T_APPEND)
			create_redir_node(shell, expand->next->word, APPEND);
		expand = expand->next;
	}
}
