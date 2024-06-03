/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/05/31 19:04:43 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <string.h>
# include <bsd/string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "builtin.h"
# include "execution.h"
# include "utils.h"

//command line front message
# define CL_NAME "[minishell]$ "

//ERROR DEFINES
# define ERR_I "Error: launch program with ./minishell and no arguments"
# define ERR_SHELL "Error: failed to initialize shell"
# define ERR_ENV "Error: failed to load environmental variables"
# define ERR_MALLOC "Error: failed to allocate memory"
# define ERR_LEXER "Error: failed to initialize lexer node"
# define ERR_EXPAND "Error: failed to initialize expand node"
# define ERR_EMPTY "Error: no nodes found in the lexer list"
# define ERR_INDEX "Error: Index out of range. Cannot delete node"
# define ERR_SYNTAX "Error: syntax error near unexpected token"
# define ERR_QUOTE "Error: quote not terminated by another quote"
# define ERR_CMD "Error: command not found"
# define ERR_NCMD ": command not found"
# define ERR_PWD "Error: failed to get current working directory"
# define ERR_PWDA "pwd: too many arguments"
# define ERR_ARG "Error: too many arguments"
# define ERR_CD " No such file or directory"
# define ERR_CDARG "minishell: cd: too many arguments"
# define ERR_CDHOME "minishell: cd: HOME not set"
# define ERR_PATH "Error: failed to find path"
# define ERR_EXP1 "minishell: export: "
# define ERR_EXP2 ": not a valid identifier"
# define ERR_DOLLAR "minishell: $$: not valid in this context"

/*outermost struct of the shell
  contains all other structs and
  variables needed for the shell to run*/
typedef struct s_shell
{
	char				*line;
	char				**env;
	char				**declare;
	char				*last_dir;
	struct s_expand		*expand;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
	int					*exit_status;
	int					*fd;
	int					*red_fd;
	int					*cmd_count;
	int					pid;
}			t_shell;

//error_seq.c
void	simple_err(char *err_str);
void	free_err(char *err_str, t_shell *shell);
void	free_shell(t_shell *shell);

//main.c
t_shell	*init_shell(t_shell *shell);
void	shell_loop(t_shell *shell);
t_shell	*init_shell(t_shell *shell);
void	reset_loop(t_shell *shell, char *msg);
void	starting_dir(t_shell *shell);

//signals.c
void	handle_sigint(int sig);
void	set_signals(void);

//testing.c
void	print_lexer(t_shell *shell);
void	print_expand(t_shell *shell);
void	print_parser(t_shell *shell);
void	test_parser_pointers(char **args, char **io, char **files);

#endif
