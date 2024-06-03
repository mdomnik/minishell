/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:43:18 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/03 20:06:50 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Tokenizes the input line and performs node processing and expansion.
 * Tokens are split by whitespace and redirection symbols, and quotes.
 * the tokenized linked list is passed to the expander function for
 * joining of tokens and environmental variable expansion.
 * 
 * @param shell The shell structure containing the input line.
 */
void	tokenizer(t_shell *shell)
{
	int	i;
	int	split;

	i = 0;
	split = 1;
	shell->line = trim_whitespace(shell);
	if (!shell->line)
		return ;
	while (shell->line[i] != '\0')
	{
		if (!is_whitespace_null(shell->line[i]))
		{
			i += node_process(shell, i, split);
			split = 0;
		}
		else
		{
			split = 1;
			i++;
		}
	}
	if (!shell->lexer)
		reset_loop(shell, ERR_CMD, shell->parser->cmd, 1);
	adjust_lexer_redir(shell);
	delete_empty_nodes(shell);
	check_final_lexer(shell);
	expander(shell);
}

/**
 * Processes a node in the shell's lexer.
 * 
 * @param shell The shell structure.
 * @param i The index of the current character in the input line.
 * @param split The index of the split character in the input line.
 * @return The number of characters processed.
 */
int	node_process(t_shell *shell, int i, int split)
{
	int	j;

	j = 0;
	if (is_quote(shell->line[i]) == 34)
		j = double_quote(shell, i, split);
	else if (is_quote(shell->line[i]) == 39)
		j = single_quote(shell, i, split);
	else
		j = word_process(shell, i, split);
	return (j);
}

/**
 * Processes a double quote in the input line and creates a new lexer token.
 * 
 * @param shell The shell structure.
 * @param i The current index in the input line.
 * @param split The split flag indicating whether the token should be split.
 * @return The number of characters processed, including the double quote.
 */
int	double_quote(t_shell *shell, int i, int split)
{
	int		j;
	t_lexer	*new;
	char	*temp;

	j = 1;
	while (shell->line[i + j] != 34 && shell->line[i + j] != '\0')
		j++;
	if (shell->line[i + j] == '\0' && shell->line[i + j] != 34)
		reset_loop(shell, ERR_QUOTE, shell->parser->cmd, 1);
	temp = ft_substr(shell->line, (i + 1), (j - 1));
	if (!temp)
		free_err(ERR_MALLOC, shell);
	new = lexernew_ms(temp, T_WORD, split, 0);
	lexeraddback_ms(&shell->lexer, new);
	return (j + 1);
}

/**
 * Processes a single quote in the input line and creates a new lexer token.
 * 
 * @param shell The shell structure.
 * @param i The index of the single quote in the input line.
 * @param split The split flag indicating whether the token should be split.
 * @return The number of characters processed, including the single quote.
 */
int	single_quote(t_shell *shell, int i, int split)
{
	int		j;
	t_lexer	*new;
	char	*temp;

	j = 1;
	while (shell->line[i + j] != 39 && shell->line[i + j] != '\0')
		j++;
	if (shell->line[i + j] == '\0' && shell->line[i + j] != 39)
		reset_loop(shell, ERR_QUOTE, shell->parser->cmd, 1);
	temp = ft_substr(shell->line, (i + 1), (j - 1));
	if (!temp)
		free_err(ERR_MALLOC, shell);
	new = lexernew_ms(temp, T_WORD, split, 1);
	lexeraddback_ms(&shell->lexer, new);
	return (j + 1);
}

/**
 * Processes a word in the shell line.
 * 
 * @param shell The shell structure.
 * @param i The starting index of the word in the shell line.
 * @param split The split flag indicating whether the 
 * word is split by a delimiter.
 * @return The number of characters processed.
 */
int	word_process(t_shell *shell, int i, int split)
{
	int		j;
	char	*temp;

	j = 0;
	while (shell->line[i + j] != 34 && shell->line[i + j] != 39 
		&& !is_whitespace_null(shell->line[i + j]))
	{
		j++;
	}
	temp = ft_substr(shell->line, i, j);
	if (!temp) 
		free_err(ERR_MALLOC, shell);
	redir_scan(temp, shell, split);
	free(temp);
	return (j);
}
