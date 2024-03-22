/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:51:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 22:43:27 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void restructure_prompt(t_prompt *prompt)
{
	// char **redir;
	print_lexer(prompt);
	group_redir(prompt);
	
	lexerfreelist_ms(&prompt->lexer);
}

void group_redir(t_prompt *prompt)
{
	t_lexer *temp;
	char    **io;
	
	io = (char **)malloc(4 * sizeof(char *));
	temp = prompt->lexer;
	while(temp->next != NULL)
	{
		if (temp->token != T_WORD && temp->next->token == T_WORD)
		{
			if (temp->token == T_PIPE)
				break;
			else if (temp->token == T_HEREDOC || temp->token == T_LESSER)
			{
				io[0] = ft_strdup(temp->word);
				io[1] = ft_strdup(temp->next->word);
			}
			else if (temp->token == T_APPEND || temp->token == T_GREATER)
			{
				io[2] = ft_strdup(temp->word);
				io[3] = ft_strdup(temp->next->word);
			}
		}
		temp = temp->next;
	}
	printf("input char: %s\n", io[0]);
	printf("input file: %s\n", io[1]);
	printf("output char: %s\n", io[2]);
	printf("output file: %s\n", io[3]);
	group_waste(prompt, temp);
}

void group_waste(t_prompt *prompt, t_lexer *temp)
{
	(void)temp;
	print_lexer(prompt);
				// 	delete_node_at_index(&temp, temp->index);
				// delete_node_at_index(&temp, temp->next->index);
}