/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/03/18 15:52:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "lexer.h"
# include "parser.h"
# include "utils.h"
#define CL_NAME "[minishell]$ "

//ERROR DEFINES
#define ERR_I "Error: too many arguments; launch program with ./minishell and no arguments"
#define ERR_ENV "Error: failed to load environmental variables"
#define ERR_MALLOC "Error: failed to allocate memory"
#define ERR_QUOTE "Error: quote not terminated by another quote"

typedef struct s_prompt
{
	char				*line;
	struct s_envll      *envp;
	struct s_lexer		*lexer;
} 				t_prompt;

typedef struct s_envll
{
	char				**env;
} 				t_envll;

//error_free.c
void simple_err(char *err_str);


//main.c
void ms_loop(t_prompt *prompt);

#endif
