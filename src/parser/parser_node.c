/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:14:01 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 16:42:28 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Sets the input and output for the given parser element.
 *
 * @param io The array of input/output strings.
 * @param element The parser element to set the input/output for.
 */
void	set_io(char **io, t_parser *element)
{
	set_input(io, element);
	set_output(io, element);
}

void	set_input(char **io, t_parser *element)
{
	if (!io[0]) 
	{
		if (element->index == 0) 
		{
			element->input = I_STDIN;
			element->i_str = "STDIN";
		}
		else 
		{
			element->input = I_PIPE;
			element->i_str = "PIPE";
		}
	}
	else 
	{
		element->input = find_redir(io[0]);
		element->i_str = ft_strdup(io[1]);
	}
}

void	set_output(char **io, t_parser *element)
{
	if (io[2] == 0 || io[3] == 0) 
	{
		element->output = O_STDOUT;
		element->o_str = NULL;
	}
	else 
	{
		element->output = find_redir(io[2]);
		element->o_str = ft_strdup(io[3]);
	}
}
