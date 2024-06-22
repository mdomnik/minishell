/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/06/22 16:10:18 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

//prototyping shell struct
typedef struct s_shell	t_shell;

typedef enum e_io
{
	NONE,
	GREAT,
	APPEND,
	LESS,
	HEREDOC,
	PIPE,
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
	int				*file_types;
	int				index;
	struct s_parser	*prev;
	struct s_parser	*next;
}	t_parser;

typedef struct s_exec
{
	int				token_count;
	char			**token;
	t_io			operator;
	struct	s_exec	*next;

}	t_exec;

typedef struct s_info
{
	char	**args;
	char	**io;
	char	**files;
	int		*file_types;
}				t_info;
//parser.c
void 	parser(t_shell *shell);
void 	create_cmd_node(t_shell *shell, t_expand *expand);
void	create_input_node(t_shell *shell, t_expand *expand);
void	create_output_node(t_shell *shell, t_expand *expand);

//parser_utils_1.c
void	adjust_exec_operand(t_shell *shell, int pipe_count);
void 	set_token_count(t_shell *shell);

//parser_utils_2.c
void	create_redir_node(t_shell *shell, char *file, int type);
void remove_nodes_till_pipe(t_shell *shell);

//prep_exec.c
// void	prep_exec(t_shell *shell);
// void	create_input_node(t_shell *shell, t_parser *parser);
// void create_output_node(t_shell *shell, t_parser *parser);
// int	count_dblptr(char **args);

//prep_exec_2.c
void	remove_pipe_on_input(t_shell *shell);
void	free_nodes_on_pipe(t_shell *shell, int pipe_count);
void	get_token_count(t_shell *shell);

//prep_exec_3.c
void remove_non_exist_input(t_shell *shell);
void purge_till_input(t_shell *shell, int i);
void check_file_existance(t_shell *shell);

//exec_struct.c
t_exec	*execfreelist_ms(t_exec **lst);
void	execaddback_ms(t_exec **lst, t_exec *new);
void	create_exec_node(t_shell *shell, char **args, int operand);
t_expand *remove_current_node(t_expand *expand);

#endif
