/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/06/24 19:55:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

//prototyping shell struct
typedef struct s_shell	t_shell;

//enum for io redirection
typedef enum e_io
{
	NONE,
	GREAT,
	APPEND,
	LESS,
	HEREDOC,
	PIPE,
}	t_io;

//exec struct for use in exection
typedef struct s_exec
{
	int				token_count;
	char			**token;
	t_io			operator;
	int				index;
	struct s_exec	*next;
}	t_exec;

//parser_helpers.c
void		adjust_exec_operand(t_shell *shell, int pipe_count);
void		set_token_count(t_shell *shell);
void		create_redir_node(t_shell *shell, char *file, int type);
void		remove_nodes_till_pipe(t_shell *shell);
void		set_index_exec(t_shell *shell);

//parser_struct.c
void		create_exec_node(t_shell *shell, char **args, int operand);
t_exec		*execfreelist_ms(t_exec **lst);
void		execaddback_ms(t_exec **lst, t_exec *new);
void		remove_exec_node_at_index(t_shell *shell, int index);

//parser.c
void		parser(t_shell *shell);
void		create_cmd_node(t_shell *shell, t_expand *expand);
int			count_args_cmd(t_expand *expand);
void		create_input_node(t_shell *shell, t_expand *expand);
void		create_output_node(t_shell *shell, t_expand *expand);

#endif
