/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/17 12:35:28 by mdomnik          ###   ########.fr       */
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


#endif
