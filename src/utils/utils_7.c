/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:43:47 by kaan              #+#    #+#             */
/*   Updated: 2024/06/25 16:55:32 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Calculates the size of a linked list of t_exec nodes.
 *
 * @param exec The head of the linked list.
 * @return The size of the linked list.
 */
size_t	exec_size(t_exec *exec)
{
	t_exec		*temp;
	size_t		size;

	temp = exec;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

/**
 * Concatenates two strings and returns the result.
 * 
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 * @return The concatenated string, or NULL if either s1 or s2 is NULL.
 */
char	*ft_strjoin_msn(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*appended;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	appended = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!appended)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_s1)
		appended[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		appended[i++] = s2[j++];
	appended[i] = '\0';
	free(s1);
	return (appended);
}

/**
 * Counts the number of tokens in an array of strings.
 *
 * @param token The array of strings representing the tokens.
 * @return The number of tokens in the array.
 */
int	get_token_count_ms(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

/**
 * Concatenates two strings and returns the result.
 * If the second string is NULL, it is treated as an empty string.
 * 
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 * @return The concatenated string, or NULL if memory allocation fails.
 */
char	*ft_strjoin_ms(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s2);
	return (new);
}

void	adjust_token_values(t_shell *shell)
{
	t_lexer	*lexer;

	lexer = shell->lexer;
	while (lexer != NULL)
	{
		if (lexer->token != T_WORD)
			if (find_redir(lexer->word) == 0)
				lexer->token = T_WORD;
		lexer = lexer->next;
	}
}
