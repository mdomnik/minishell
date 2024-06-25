/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:36:31 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/25 16:50:10 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Scans the given string for redirection symbols and forms tokens accordingly.
 * 
 * @param str The string to be scanned.
 * @param shell The shell structure containing relevant information.
 */
void	redir_scan(char *str, t_shell *shell, int split)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (check_redir(str[i], str[i + 1], 1) == T_WORD)
		{
			i += form_word(str, shell, i, split);
			split = 0;
		}
		else
		{
			i += form_redir(str, shell, i);
			split = 1;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
}

/**
 * @brief Forms a word token from a given string
 * and adds it to the lexer.
 * 
 * This function takes a string, starting from the given index,
 * and forms a word token
 * by checking for consecutive characters that are not
 *redirection symbols. It then creates
 * a new lexer node with the formed word token and adds it to 
 * the lexer linked list.
 * 
 * @param str The input string.
 * @param shell The shell structure.
 * @param i The starting index in the string.
 * @return The number of characters processed to form the word token.
 */
int	form_word(char *str, t_shell *shell, int i, int split)
{
	int		j;
	char	*temp;
	t_lexer	*new;

	j = 0;
	temp = NULL;
	while (str[i + j + 1] != '\0' 
		&& check_redir(str[i + j], str[i + j + 1], 0) == T_WORD)
		j++;
	temp = ft_substr(str, i, j + 1);
	if (!temp)
		free_err(ERR_MALLOC, shell);
	new = lexernew_ms(temp, T_WORD, split, 0);
	lexeraddback_ms(&shell->lexer, new);
	return (j);
}

/**
 * Forms a redirection token from a given string and adds it to the lexer.
 *
 * @param str The input string.
 * @param shell The shell structure.
 * @param i The current index in the input string.
 * @return The number of characters consumed from the input string.
 */
int	form_redir(char *str, t_shell *shell, int i)
{
	int		j;
	int		type;
	char	*temp;
	t_lexer	*new;

	temp = NULL;
	type = check_redir(str[i], str[i + 1], 1);
	if (type >= 1 && type <= 3)
		j = 1;
	else
		j = 2;
	temp = ft_substr(str, i, j);
	if (!temp)
		free_err(ERR_MALLOC, shell);
	new = lexernew_ms(temp, type, 1, 0);
	lexeraddback_ms(&shell->lexer, new);
	return (j - 1);
}

/**
 * Checks the type of redirection based on the given characters.
 *
 * @param c1 The first character to compare.
 * @param c2 The second character to compare.
 * @return The type of redirection:
 *         - T_APPEND if c1 and c2 are '>', and c2 is not '\0'.
 *         - T_HEREDOC if c1 and c2 are '<', and c2 is not '\0'.
 *         - T_MISTAKE if c1 is '<' and c2 is '>', and c2 is not '\0'.
 *         - T_GREATER if c1 or c2 is '>'.
 *         - T_LESSER if c1 or c2 is '<'.
 *         - T_PIPE if c1 or c2 is '|'.
 *         - T_WORD if none of the above conditions are met.
 */
int	check_redir(char c1, char c2, int test)
{
	if (!cmpchar(c1, '>') && !cmpchar(c2, '>') && c2 != '\0')
		return (T_APPEND);
	else if (!cmpchar(c1, '<') && !cmpchar(c2, '<') && c2 != '\0')
		return (T_HEREDOC);
	else if (!cmpchar(c1, '<') && !cmpchar(c2, '>') && c2 != '\0')
		return (T_MISTAKE);
	else if (!cmpchar(c1, '>') || !cmpchar(c2, '>'))
		return (T_GREATER);
	else if (!cmpchar(c1, '<') || !cmpchar(c2, '<'))
		return (T_LESSER);
	else if ((!cmpchar(c1, '|') || !cmpchar(c2, '|')) && test == 0)
		return (T_PIPE);
	else if ((!cmpchar(c1, '|')) && test == 1)
		return (T_PIPE);
	return (T_WORD);
}

/**
 * Compares two characters and returns the difference between them.
 * 
 * @param c1 The first character to compare.
 * @param c2 The second character to compare.
 * @return The difference between the two characters.
 */
int	cmpchar(char c1, char c2)
{
	if (c1 != c2)
		return (c1 - c2);
	return (0);
}
