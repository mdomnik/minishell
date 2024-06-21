/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/06/21 15:00:24 by mdomnik          ###   ########.fr       */
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

//parser_node.c
void		set_io(char **io, t_parser *element);
void		set_input(char **io, t_parser *element);
void		set_output(char **io, t_parser *element);

//parser_struct.c
t_parser	*parsernew_ms(char **args, char **io,
				char **files, int *file_types);
int			reset_increment_k(int x);
void		parseraddback_ms(t_parser **lst, t_parser *new);
t_parser	*parserfreelist_ms(t_parser **lst);

//parser_utils_1.c
char		**pop_io(char **io, char *str1, char *str2, int token);
char		**remove_first(char **args);
int			find_redir(char *str);
int			ft_memcmp_ms(const void *s1, const void *s2);

//parser_utils_2.c
void		purge_redir(t_shell *shell);
void		delete_node(t_shell *shell, t_expand *current);
void		free_io(char **double_str);
void		create_parser_node(t_shell *shell, t_info info);
void		adjust_output(t_shell *shell);

//parser_utils_3.c
void		handle_token(t_expand *cur, char **io, int *file_num);
int			count_args_before_pipe(t_expand *expand);

//parser.c
void		parser(t_shell *shell);
void		group_redir(t_shell *shell);
void		group_files(t_shell *shell, char **io, int file_num);
void		group_args(t_shell *shell, char **io,
				char **files, int *file_types);

//prep_exec.c
void	prep_exec(t_shell *shell);
void	create_exec_node(t_shell *shell, t_parser *parser,char **args, char *cmd);
void	create_input_node(t_shell *shell, t_parser *parser);
void create_output_node(t_shell *shell, t_parser *parser);
int	count_dblptr(char **args);

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

#endif
