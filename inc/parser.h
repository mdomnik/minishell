/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:46 by kaan              #+#    #+#             */
/*   Updated: 2024/04/19 17:49:26 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

//prototyping shell struct
typedef struct s_shell	t_shell;

typedef enum e_io
{
	I_STDIN = 10,
	O_STDOUT = 20,
	I_PIPE = 30,
	O_PIPE = 40,
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
	int				index;
	struct s_parser	*prev;
	struct s_parser	*next;
}	t_parser;

//parser_struct.c
t_parser	*parsernew_ms(char **args, char **io, char **files);
int			reset_increment_k(int x);
void		parseradd_back(t_parser **lst, t_parser *new);

//parser_utils_1.c
char **pop_io(char **io, char *str1, char *str2 , int token);
char **remove_first(char **args);
int	find_redir(char *str);
int	ft_memcmp_ms(const void *s1, const void *s2);

//parser_utils_2.c
void purge_redir(t_shell *shell);
void delete_node(t_shell *shell, t_expand *current);

//parser.c
void	parser(t_shell *shell);
void	group_redir(t_shell *shell);
void	group_files(t_shell *shell, char **io, int file_num);
void	group_args(t_shell *shell, char **io, char **files);

#endif
