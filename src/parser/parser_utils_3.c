/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:28:40 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 17:10:40 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief counts files before pipe
 * 
 * Counts the number of output files and populates the io array in pop_io.
 * 
 * @param cur The current token to handle.
 * @param io The input/output redirection array.
 * @param file_num The number of files.
 */
void	handle_token(t_expand *cur, char **io, int *file_num)
{
	if (cur->token == T_LESSER || cur->token == T_HEREDOC)
	{
		io = pop_io(io, cur->word, cur->next->word, cur->token);
	}
	else if (cur->token == T_GREATER || cur->token == T_APPEND)
	{
		io = pop_io(io, cur->word, cur->next->word, cur->token);
		(*file_num)++;
	}
}

/**
 * Counts the number of arguments before a pipe token in the given expand list.
 *
 * @param expand The expand list to count the arguments from.
 * @return The number of arguments before the pipe token.
 */
int	count_args_before_pipe(t_expand *expand)
{
	t_expand	*current;
	int			arg_num;

	current = expand;
	arg_num = 0;
	while (current != NULL)
	{
		if (current->token == T_PIPE)
			break ;
		arg_num++;
		current = current->next;
	}
	return (arg_num);
}
