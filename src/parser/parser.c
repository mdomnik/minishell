/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:51:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 18:04:35 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void restructure_prompt(t_prompt *prompt)
{
	// char **redir;
	print_lexer(prompt);
	// redir = group_redir(prompt->lexer);
	
	lexerfreelist_ms(&prompt->lexer);
}

// char **group_redir(t_lexer *lexer)
// {
// 	char **ret;
// 	int i;
	
	
// 	i = 0;
// }