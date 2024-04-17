/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/04/17 20:31:49 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

//prototyping shell struct
typedef struct s_shell	t_shell;

typedef enum e_io
{
	I_STDIN = 10,
	O_STDOUT = 20,
	I_PIPE = 30,
	O_PIPE = 40,
}	t_io;

typedef struct s_parser
{
	char			*cmd;
	char			**args;
	int				input;
	char			*i_str;
	int				output;
	char			*o_str;
	char			**files;
	int				index;
	struct s_parser	*prev;
	struct s_parser	*next;
}	t_parser;

//parser.c
void	parser(t_shell *shell);

#endif
