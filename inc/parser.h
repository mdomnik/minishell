/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/21 13:36:30 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

//prototyping prompt struct
typedef struct s_prompt t_prompt;


typedef struct s_redir //become redirection
{
	int					redirection;
	char				*content;
	struct  s_parser	*prev;
	struct  s_parser	*next;
} t_redir;

typedef struct s_args //become args
{
	char			*content;
	int				 index;	
	struct  s_args	 *prev;
	struct  s_args	 *next;
} t_args;

typedef struct s_parser
{
	char				*cmd;
	char				*options;
	int					index;
	struct  s_args   	*args;
	struct  s_redir  	*redir; 
	struct  s_args	 	*prev;
	struct  s_args	 	*next;
} t_parser;

typedef struct s_exec
{
	char				*cmd; //command to search for teh executable
	char				**args; //list of arguments for the command

	int					input; //input type
	char				*i_str; //inpur file

	int					output; //output type
	char				*o_str; //output file

	char				**files; //when multiple I/O check for names and create empties
	int					index; //which command in the sequence

	struct  s_exec	 	*prev; //address of previous node
	struct  s_exec	 	*next; //address of next node
} t_exec;

#endif
