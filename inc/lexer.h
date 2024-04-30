/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:41:48 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/30 17:11:29 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

//TOKENS
typedef enum e_tokens
{
	T_WORD = 0,
	T_PIPE = 1,
	T_GREATER = 2,
	T_LESSER = 3,
	T_HEREDOC = 4,
	T_APPEND = 5,
	T_MISTAKE = 6,
}	t_tokens;

/* struct for lexer linked list
stores words(delimited by whitespace), tokens (from e_token enum),
position in the index, adresses of previous and next nodes */
typedef struct s_lexer
{
	char			*word;
	t_tokens		token;
	int				join;
	int				quote;
	int				index;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}			t_lexer;

//lexer_redir.c
void		redir_scan(char *str, t_shell *shell, int split);
int			form_word(char *str, t_shell *shell, int i, int split);
int			form_redir(char *str, t_shell *shell, int i);
int			check_redir(char c1, char c2);
int			cmpchar(char c1, char c2);

//lexer_struct.c
t_lexer		*lexernew_ms(char *word, t_tokens token, int join, int quote);
int			reset_increment_i(int x);
void		lexeraddback_ms(t_lexer **lst, t_lexer *new);
t_lexer		*lexerfreelist_ms(t_lexer **lst);
void		delete_empty_nodes(t_shell *shell);

//lexer_word.c
char		*trim_whitespace(t_shell *shell);
int			is_whitespace_null(char c);
int			is_quote(char c);
int			check_whitespace(char *str);
int			inc_whitespace(t_shell *shell, int i);

//lexer.c
void		tokenizer(t_shell *shell);
int			node_process(t_shell *shell, int i, int split);
int			double_quote(t_shell *shell, int i, int split);
int			single_quote(t_shell *shell, int i, int split);
int			word_process(t_shell *shell, int i, int split);
#endif