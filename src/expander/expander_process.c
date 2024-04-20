/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:56 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/20 19:52:00 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_lexer(t_shell *shell, t_lexer *lexer, char *string, int boolean)
{
	t_expand	*new;

	while (lexer != NULL)
	{
		if (lexer->join == 1 && boolean == 1)
			boolean = create_node(string, lexer->prev->token, shell);
		if (lexer->join == 1 && boolean == 0)
		{
			string = ft_strdup(lexer->word);
			boolean = 1;
		}
		if (lexer->join == 0)
		{
			string = ft_strjoin(string, lexer->word);
			boolean = 1;
		}
		if (lexer->next == NULL && boolean == 1)
		{
			new = expandnew_ms(string, lexer->token);
			expandaddback_ms(&shell->expand, new);
		}
		lexer = lexer->next;
	}
}

int	create_node(char *word, int token, t_shell *shell)
{
	t_expand	*new;

	new = expandnew_ms(word, token);
	expandaddback_ms(&shell->expand, new);
	word = NULL;
	return (0);
}
