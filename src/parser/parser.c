/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:28:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 22:36:51 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_shell *shell)
{
	t_expand	*expand;
	int			i;

	i = 0;
	expand = shell->expand;
	while(expand != NULL)
	{
		create_cmd_node(shell, expand);
		create_input_node(shell, expand);
		create_output_node(shell, expand);
		remove_nodes_till_pipe(shell);
		adjust_exec_operand(shell, i);
		i++;
		expand = shell->expand;
	}
	set_token_count(shell);
	set_index_exec(shell);
	//print_exec(shell);
	//reset_loop(shell);
	execution(shell);
}

void	create_cmd_node(t_shell *shell, t_expand *expand)
{
	char **args;
	int i;

	i = 0;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_WORD && (expand->prev == NULL || expand->prev->token == T_WORD))
			i++;
		expand = expand->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	expand = shell->expand;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_WORD && (expand->prev == NULL || expand->prev->token == T_WORD))
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

void	create_input_node(t_shell *shell, t_expand *expand)
{
	t_expand *temp;

	temp = expand;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_LESSER)
			create_redir_node(shell, expand->next->word, LESS);
		expand = expand->next;
	}
	expand = temp;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_HEREDOC)
			create_redir_node(shell, expand->next->word, HEREDOC);
		expand = expand->next;
	}
}

void	create_output_node(t_shell *shell, t_expand *expand)
{
	t_expand *temp;

	temp = expand;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_GREATER)
			create_redir_node(shell, expand->next->word, GREAT);
		expand = expand->next;
	}
	expand = temp;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_APPEND)
			create_redir_node(shell, expand->next->word, APPEND);
		expand = expand->next;
	}
}