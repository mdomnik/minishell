/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:56 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/20 20:17:06 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Process the lexer and expand the tokens into a string.
 * joins the tokens together and creates a new node.
 * 
 * @param shell   The shell structure.
 * @param lexer   The lexer structure.
 * @param string  The string to be expanded.
 * @param boolean A flag indicating whether to create a new node or not.
 */
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

/**
 * Creates a new expand node and adds it to the expand list in the shell.
 *	(Supportive Function)
 * @param word The word to be expanded.
 * @param token The token associated with the word.
 * @param shell The shell structure.
 * @return 0 on success.
 */
int	create_node(char *word, int token, t_shell *shell)
{
	t_expand	*new;

	new = expandnew_ms(word, token);
	expandaddback_ms(&shell->expand, new);
	word = NULL;
	return (0);
}
