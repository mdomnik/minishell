/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/24 19:27:17 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

//prototyping prompt struct
typedef struct s_prompt t_prompt;

typedef enum e_io
{
    I_STDIN = 10,
    O_STDOUT = 20,
    I_PIPE = 30,
    O_PIPE = 40,
} t_io;

typedef struct s_parser
{
    char                *cmd; //command to search for the executable
    char                **args; //list of arguments for the command

    int                 input; //input type
    char                *i_str; //input file

    int                 output; //output type
    char                *o_str; //output file

    char                **files; //when multiple I/O check for names and create empties
    
    int                 index; //which command in the sequence

    struct  s_parser      *prev; //address of previous node
    struct  s_parser      *next; //address of next node
} t_parser;

//parser.c
void restructure_prompt(t_prompt *prompt);
void group_redir(t_prompt *prompt);
void group_files(t_prompt *prompt, t_lexer *temp, int create, char **io);
void group_args(t_prompt *prompt, t_lexer *temp, char **io, char **files);

#endif
