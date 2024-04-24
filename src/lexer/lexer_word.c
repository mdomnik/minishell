/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:43:48 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/24 23:12:08 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Trims leading and trailing whitespace from a string.
 * 
 * @param str The string to trim.
 * @param shell A pointer to the shell structure.
 * @return A pointer to the trimmed string.
 */
char	*trim_whitespace(t_shell *shell)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	j = (ft_strlen_ms(shell->line) - 1);
	i = 0;
	k = 0;
	if (j == 0)
		return (NULL);
	while (shell->line[i] == 32 
		|| (shell->line[i] >= 9 && shell->line[i] <= 13))
		i++;
	while (shell->line[j] == 32 
		|| (shell->line[j] >= 9 && shell->line[j] <= 13))
		j--;
	temp = malloc((j - i) + 2);
	if (!temp)
		return (NULL);
	while ((i + k) <= j)
	{
		temp[k] = shell->line[i + k];
		k++;
	}
	temp[k] = '\0';
	free(shell->line);
	return (temp);
}

/**
 * Checks if a character is a whitespace or null character.
 *
 * @param c The character to check.
 * @return 1 if the character is a whitespace or null character, 0 otherwise.
 */
int	is_whitespace_null(char c)
{
	if (c == 32 || (c >= 9 && c <= 13) || c == '\0')
		return (1);
	return (0);
}

/**
 * Checks if a character is a quote.
 *
 * @param c The character to check.
 * @return Returns the ASCII value of the quote character
 * if it is a quote, otherwise returns 0.
 * 34 for double quote, 39 for single quote, 0 otherwise.
 */
int	is_quote(char c)
{
	if (c == 34)
		return (34);
	else if (c == 39)
		return (39);
	else
		return (0);
}
