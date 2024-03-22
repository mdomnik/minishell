/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:12:05 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 16:04:19 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

//prototyping prompt struct
typedef struct s_prompt t_prompt;

//main_utils.c
t_prompt *init_prompt(t_prompt *prompt);
char	**double_dup(char **str);
void	free_double(char **double_str);
void	print_lexer(t_prompt *prompt);

//lexer_struct.c
t_lexer	*lexernew_ms(char *word, t_tokens token);
void	lexeraddback_ms(t_lexer **lst, t_lexer *new);
t_lexer *lexerfreelist_ms(t_lexer **lst);
void delete_node_at_index(t_lexer **lexer, int index);
int	reset_increment_i(int x);

//lexer_utils.c
char *trim_whitespace(char *str);
int is_whitespace_null(char c);
int is_quote(char c);
char	*append_char_env(char *str, char c);
char	*removed_env(char *str);

//lexer_utils_2.c
int	find_redir(char *str);
int	ft_memcmp_ms(const void *s1, const void *s2);
int	ft_strlen_ms(char *s);
void add_node(t_prompt *prompt, char *word, t_tokens token);

//lexer_utils_3.c
char *search_redir(t_prompt *prompt, char *str, char *word);
int	check_redir(char c1, char c2);
int	cmpchar(char c1, char c2);

#endif