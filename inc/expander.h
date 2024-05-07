/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:00:12 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/07 15:26:12 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

//prototyping prompt struct
typedef struct s_shell	t_shell;

typedef struct s_expand
{
	char			*word;
	int				token;
	int				index;
	struct s_expand	*prev;
	struct s_expand	*next;
}		t_expand;

//expander_process.c
void		process_lexer(t_shell *shell,
				t_lexer *lexer, char *string, int boolean);
int			create_node(char *word, int token, t_shell *shell);

//expander_struct.c
t_expand	*expandnew_ms(char *word, int token);
int			reset_increment_j(int x);
void		expandaddback_ms(t_expand **lst, t_expand *new);
t_expand	*expandfreelist_ms(t_expand **lst);

//expander.c
void		expander(t_shell *shell);
void		env_expander(t_lexer *lexer, int i, t_shell *shell);
char	*search_replace_env(char *str, t_shell *shell);


#endif