/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:24:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/21 15:09:58 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*change parser into shortest executable sequence*/
void prep_exec(t_shell *shell)
{
	t_parser *parser;
	parser = shell->parser;
	while (parser != NULL)
	{
		create_exec_node(shell, parser, parser->args, parser->cmd);
		if (parser->input != NONE && parser->input != PIPE)
			create_input_node(shell, parser);
		if (parser->output != NONE && parser->output != PIPE)
			create_output_node(shell, parser);
		if (parser->output != PIPE)
			break;
		parser = parser->next;
	}
	remove_pipe_on_input(shell);
	remove_non_exist_input(shell);
	get_token_count(shell);
	check_file_existance(shell);
	// print_exec(shell);
	parserfreelist_ms(&shell->parser);
	execution(shell);
}

void	create_exec_node(t_shell *shell, t_parser *parser, char **args, char *cmd)
{
	t_exec	*node;
	char	**token;
	int		i;

	i = 0;
	node = (t_exec *)malloc(sizeof(t_exec));
	token = (char **)malloc((count_dblptr(args) + 2) * sizeof(char *));
	if (!cmd)
		return ;
	token[0] = ft_strdup(cmd);
	while (i < (count_dblptr(args)))
	{
		token[i + 1] = ft_strdup(args[i]);
		i++;
	}
	token[i + 1] = NULL;
	if (parser->input != NONE && parser->input != PIPE)
		node->operator = parser->input;
	else
		node->operator = parser->output;
	node->token = token;
	node->token_count = 0;
	node->next = NULL;
	execaddback_ms(&shell->exec, node);
}

void create_input_node(t_shell *shell, t_parser *parser)
{
	t_exec	*node;
	char	**token;

	node = (t_exec *)malloc(sizeof(t_exec));
	token = (char **)malloc(2 * sizeof(char *));
	token[0] = ft_strdup(parser->i_str);
	token[1] = NULL;
	if (parser->output != NONE)
		node->operator = parser->output;
	else
		node->operator = NONE;
	node->token = token;
	node->token_count = 0;
	node->next = NULL;
	execaddback_ms(&shell->exec, node);
}
void create_output_node(t_shell *shell, t_parser *parser)
{
	t_exec	*node;
	char	**token;

	node = (t_exec *)malloc(sizeof(t_exec));
	token = (char **)malloc(2 * sizeof(char *));
	token[0] = ft_strdup(parser->o_str);
	token[1] = NULL;
	node->operator = NONE;
	node->token = token;
	node->token_count = 0;
	node->next = NULL;
	execaddback_ms(&shell->exec, node);
}

int	count_dblptr(char **args)
{
	int	i;

	i = 0;
	while(args[i] != NULL)
		i++;
	return (i);
}
