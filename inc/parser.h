/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/22 16:33:38 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

//prototyping prompt struct
typedef struct s_prompt t_prompt;

typedef struct s_parser
{
    char                *cmd; //command to search for the executable
    char                **args; //list of arguments for the command

    int                 input; //input type
    char                *i_str; //inpur file

    int                 output; //output type
    char                *o_str; //output file

    char                **files; //when multiple I/O check for names and create empties
    int                 index; //which command in the sequence

    struct  s_parser      *prev; //address of previous node
    struct  s_parser      *next; //address of next node
} t_parser;

//parser.c
void restructure_prompt(t_prompt *prompt);


#endif
