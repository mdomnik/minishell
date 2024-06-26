/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/26 12:37:30 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <bsd/string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
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
# define ERR_I " launch program with ./minishell and no arguments"
# define ERR_SHELL " failed to initialize shell"
# define ERR_ENV " failed to load environmental variables"
# define ERR_MALLOC " failed to allocate memory"
# define ERR_LEXER " failed to initialize lexer node"
# define ERR_EXPAND " failed to initialize expand node"
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_QUOTE " quote not terminated by another quote"
# define ERR_CMD " command not found"
# define ERR_PWD " failed to get current working directory"
# define NO_FILE " No such file or directory"
# define NO_PERMIT " Permission denied"

/*outermost struct of the shell
  contains all other structs and
  variables needed for the shell to run*/
typedef struct s_shell
{
	char				*line;
	char				**env;
	char				**declare;
	struct s_expand		*expand;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
	struct s_exec		*exec;
	int					*exit_status;
	int					in_fd;
	int					out_fd;
}			t_shell;

//error_seq.c
void	simple_err(char *err_str);
void	free_err(char *err_str, t_shell *shell);
void	ft_perror(char *msg, char *cmd, unsigned int err, t_shell *shell);
void	free_shell(t_shell *shell);

//main.c
t_shell	*init_shell(t_shell *shell);
void	shell_loop(t_shell *shell);
t_shell	*init_shell(t_shell *shell);
void	reset_loop(t_shell *shell);

//signals.c
void	child_signals(int signum);
void	dismiss_signal(int signum);
void	config_signals(void);

//signals_2.c
void	sigquit_handler(int num);
void	sigint_handler_child(int num);
void	set_signals_child(void);

//testing.c
void	print_lexer(t_shell *shell);
void	print_expand(t_shell *shell);
void	test_parser_pointers(char **args, char **io, char **files);
void	print_exec(t_shell *shell);
void	print_double_pointer(char **list);
void	print_triple_pointer(char ***triple_pointer);

#endif
