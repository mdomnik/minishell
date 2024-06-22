/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:24:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 15:58:31 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// /*change parser into shortest executable sequence*/
// void prep_exec(t_shell *shell)
// {
// 	t_parser *parser;
// 	parser = shell->parser;
// 	while (parser != NULL)
// 	{
// 		// create_exec_node(shell, parser, parser->args, parser->cmd);
// 		if (parser->input != NONE && parser->input != PIPE)
// 			create_input_node(shell, parser);
// 		if (parser->output != NONE && parser->output != PIPE)
// 			create_output_node(shell, parser);
// 		if (parser->output != PIPE)
// 			break;
// 		parser = parser->next;
// 	}
// 	remove_pipe_on_input(shell);
// 	remove_non_exist_input(shell);
// 	get_token_count(shell);
// 	check_file_existance(shell);
// 	// print_exec(shell);
// 	execution(shell);
// }

// void create_input_node(t_shell *shell, t_parser *parser)
// {
// 	t_exec	*node;
// 	char	**token;

// 	node = (t_exec *)malloc(sizeof(t_exec));
// 	token = (char **)malloc(2 * sizeof(char *));
// 	token[0] = ft_strdup(parser->i_str);
// 	token[1] = NULL;
// 	if (parser->output != NONE)
// 		node->operator = parser->output;
// 	else
// 		node->operator = NONE;
// 	node->token = token;
// 	node->token_count = 0;
// 	node->next = NULL;
// 	execaddback_ms(&shell->exec, node);
// }
// void create_output_node(t_shell *shell, t_parser *parser)
// {
// 	t_exec	*node;
// 	char	**token;

// 	node = (t_exec *)malloc(sizeof(t_exec));
// 	token = (char **)malloc(2 * sizeof(char *));
// 	token[0] = ft_strdup(parser->o_str);
// 	token[1] = NULL;
// 	node->operator = NONE;
// 	node->token = token;
// 	node->token_count = 0;
// 	node->next = NULL;
// 	execaddback_ms(&shell->exec, node);
// }