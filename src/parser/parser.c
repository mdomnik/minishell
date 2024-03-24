/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:51:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/24 19:28:13 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void restructure_prompt(t_prompt *prompt)
{
	// char **redir;
	print_lexer(prompt);
	reset_increment_j(0);
	group_redir(prompt);
	parser_check_out(prompt);
	print_parser(prompt);
	// lexerfreelist_ms(&prompt->lexer);
}

void group_redir(t_prompt *prompt)
{
	t_lexer *temp;
	char    **io;
	int	 create;

	create = 0;	
	io = (char **)ft_calloc((5), sizeof(char *));
	temp = prompt->lexer;
	while(temp->next != NULL)
	{
		if (temp->token != T_WORD && temp->next->token == T_WORD)
		{
			if (temp->token == T_PIPE)
				break ;
			else if (temp->token == T_HEREDOC || temp->token == T_LESSER)
			{
				io[0] = ft_strdup(temp->word);
				io[1] = ft_strdup(temp->next->word);
			}
			else if (temp->token == T_APPEND || temp->token == T_GREATER)
			{
				io[2] = ft_strdup(temp->word);
				io[3] = ft_strdup(temp->next->word);
				create++;
			}
		}
		io[4] = NULL;
		temp = temp->next;
	}
	
	group_files(prompt, prompt->lexer, create, io);
}

void group_files(t_prompt *prompt, t_lexer *temp, int create, char **io)
{
	char **files;
	int i;
	t_lexer *next_node;

	i = 0;
	files = (char **)malloc((create + 1) * sizeof(char *));
	while(temp != NULL)
	{
		next_node = temp->next;
		if (temp->token != T_WORD && next_node && next_node->token == T_WORD)
		{
			if (temp->token == T_PIPE)
				break ;
			else if (temp->token == T_HEREDOC || temp->token == T_LESSER)
			{
				delete_node_at_index(&temp, temp->index);
				if (next_node)
					delete_node_at_index(&temp, next_node->index);
			}
			else if (temp->token == T_APPEND || temp->token == T_GREATER)
			{
				files[i] = ft_strdup(next_node->word);
				if (next_node)
					delete_node_at_index(&temp, next_node->index);
				delete_node_at_index(&temp, temp->index);
				i++;
			}
		}
		temp = next_node;
	}
	files[i] = NULL;
	group_args(prompt, prompt->lexer, io, files);
}

void group_args(t_prompt *prompt, t_lexer *temp, char **io, char **files)
{
	t_parser *new;
	char **args;
	int	i;

	i = 0;
	while(temp != NULL)
	{
		temp->index = i;
		i++;
		temp = temp->next;
	}
	args = (char **)malloc((i + 1) * sizeof(char *));
	temp = prompt->lexer;
	i = 0;
	while (temp != NULL)
	{
		if (temp->token == T_PIPE)
			break ;
		args[i] = ft_strdup(temp->word);
		if (args[i] == NULL)
			simple_err(ERR_MALLOC);
		delete_node_at_index(&prompt->lexer, 0);
		i++;
		temp = temp->next;
	}
	
	args[i] = NULL;
    new = parsernew_ms(args, io, files);
	printf("new->cmd: %s\n", new->cmd);
	parseraddback_ms(&prompt->parser, new);
	printf("prompt->parser->cmd: %s\n", prompt->parser->cmd);
	temp = prompt->lexer;
	if (io) 
	{
		free_double(io);
		io = NULL;
	}
	if (files)
	{
		free_double(files);
		files = NULL; 
	}
	if (temp == NULL)
		return ;
	if (temp->token == T_PIPE && temp->next != NULL)
	{
		delete_node_at_index(&prompt->lexer, 0);
		restructure_prompt(prompt);
	}
}
