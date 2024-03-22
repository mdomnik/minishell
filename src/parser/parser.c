/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:51:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 17:33:49 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void restructure_prompt(t_prompt *prompt)
{
	print_lexer(prompt);
	
	
	lexerfreelist_ms(&prompt->lexer);
}