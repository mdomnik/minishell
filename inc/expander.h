/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:00:12 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/25 20:37:06 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

/**
 * @struct t_expand
 * @brief Represents an expand structure.
 *
 * The `t_expand` struct is used to store information about an expand operation.
 * It contains a word, a token, an index, and pointers to the previous
 * and next expand structures.
 */
typedef struct s_expand
{
	char			*word;
	int				token;
	int				index;
	struct s_expand	*next;
	struct s_expand	*prev;
}			t_expand;

//expander_delim.c
char		**add_delim_split(char *str, t_shell *shell);
char		**double_dollar(char *str, int i);
char		**single_dollar(void);
void		free_err_delim(t_shell *shell, char **ret);

//expander_process.c
void		process_lexer(t_shell *shell, t_lexer *lexer,
				char *string, int boolean);
int			create_node(char *word, int token, t_shell *shell);
t_expand	*remove_empty_node(t_shell *shell, t_expand *expand);
t_expand	*remove_empty_node_2(t_shell *shell, t_expand *expand);
void		remove_empty_expand(t_shell *shell);

//expander_struct.c
t_expand	*expandnew_ms(char *word, int token);
int			reset_increment_j(int x);
void		expandaddback_ms(t_expand **lst, t_expand *new);
t_expand	*expandfreelist_ms(t_expand **lst);

//expander.c
void		expander(t_shell *shell);
void		env_expander(t_lexer *lexer, int i, t_shell *shell);
char		*search_replace_env(char *str, t_shell *shell, int i, int j);
char		*give_ret_search_replace(t_shell *shell, char *temp);

#endif
