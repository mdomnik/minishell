/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:51:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/24 14:34:05 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void restructure_prompt(t_prompt *prompt)
{
	// char **redir;
	// print_lexer(prompt);
	group_redir(prompt);
	lexerfreelist_ms(&prompt->lexer);
}

void group_redir(t_prompt *prompt)
{
	t_lexer *temp;
	char    **io;
	int	 create;

	create = 0;	
	io = (char **)malloc(4 * sizeof(char *));
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
		temp = temp->next;
	}
	group_files(prompt, prompt->lexer, create, io);
}

void group_files(t_prompt *prompt, t_lexer *temp, int create, char **io)
{
	char **files;
	int i;

	i = 0;
	files = (char **)malloc((create + 1) * sizeof(char *));
	while(temp->next != NULL)
	{
		if (temp->token != T_WORD && temp->next->token == T_WORD)
		{
			if (temp->token == T_PIPE)
				break ;
			else if (temp->token == T_HEREDOC || temp->token == T_LESSER)
			{
				delete_node_at_index(&temp, temp->index);
				delete_node_at_index(&temp, temp->next->index);
			}
			else if (temp->token == T_APPEND || temp->token == T_GREATER)
			{
				files[i] = ft_strdup(temp->next->word);
				delete_node_at_index(&temp, temp->next->index);
				delete_node_at_index(&temp, temp->index);
				i++;
			}
		}
		temp = temp->next;
	}
	files[i] = NULL;
	group_args(prompt, prompt->lexer, io, files);
}

void group_args(t_prompt *prompt, t_lexer *temp, char **io, char **files)
{
	char **args;
	int i;

	if (!prompt || !temp || !io || !files) {
		printf("One of the input parameters is NULL.\n");
		return;
	}

	i = 0;
	while(temp != NULL)
	{
		temp->index = i;
		i++;
		temp = temp->next;
	}
	args = (char **)malloc((i + 1) * sizeof(char *));
	if (!args) {
		printf("Memory allocation failed.\n");
		return;
	}
	temp = prompt->lexer;
	i = 0;
	print_lexer(prompt);
	while (temp != NULL)
	{
		if (temp->token == T_PIPE)
			break ;
		if (!temp->word) {
			printf("temp->word is NULL.\n");
			break;
		}
		args[i] = ft_strdup(temp->word);
		printf("temp->index: %d\n", temp->index);
		delete_node_at_index(&temp, temp->index);
		i++;
		temp = temp->next;
	}
	args[i] = NULL;
	printf("input: [%s] ", io[0]);
	printf("| file: [%s]\n", io[1]);
	printf("output: [%s] ", io[2]);
	printf("| file: [%s]\n", io[3]);
	i = 0;
	printf("files: ");
	while (files[i] != NULL)
	{
		printf("[%s]", files[i]);
		i++;
	}
	printf("\nargs: ");
	i = 0;
	while (args[i] != NULL)
	{
		printf("[%s]", args[i]);
		i++;
	}
	printf("\n");
	print_lexer(prompt);
}
