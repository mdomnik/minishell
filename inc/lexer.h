/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:41:48 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 16:08:58 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

//prototyping prompt struct
typedef struct s_prompt t_prompt;

//gives num values to operators (tokenizes)
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

//struct for lexer linked list
//stores words(delimited by whitespace), tokens (from s_token struct),
//position in the index, adresses of previous and next nodes
typedef struct s_lexer
{
	char			*word;
	t_tokens		token;
	int				index;
	struct s_lexer	*prev;
	struct s_lexer	*next;
} t_lexer;

//lexer.c
void split_tokens(t_prompt *prompt);
int	node_process(t_prompt *prompt, int	i, char *temp);
char	*search_replace_env(char *str);
char	*replace_env(char	*env_name, char	*env_str);
char 	*updated_env_str(char *str, char	*env_str);
#endif