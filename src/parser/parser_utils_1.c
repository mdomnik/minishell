/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:53:27 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/10 16:38:09 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Populates the io array with the given strings based on the token type.
 *
 * @param io The io array to populate.
 * @param str1 The first string to copy into the io array.
 * @param str2 The second string to copy into the io array.
 * @param token The token type indicating the operation to perform.
 * @return The updated io array.
 */
char	**pop_io(char **io, char *str1, char *str2, int token)
{
	if (token == T_LESSER || token == T_HEREDOC)
	{
		if (io[0])
			free(io[0]);
		if (io[1])
			free(io[1]);
		io[0] = ft_strdup(str1);
		io[1] = ft_strdup(str2);
	}
	else if (token == T_GREATER || token == T_APPEND)
	{
		if (io[2])
			free(io[2]);
		if (io[3])
			free(io[3]);
		io[2] = ft_strdup(str1);
		io[3] = ft_strdup(str2);
	}
	return (io);
}

/**
 * Removes the first element from an array of strings.
 * 
 * @param args The array of strings from which to remove the first element.
 * @return A new array of strings without the first element.
 */
char	**remove_first(char **args)
{
	char	**temp;
	int		i;

	i = 0;
	if (args == NULL || args[0] == NULL)
		return (NULL);
	while (args[i] != NULL)
		i++;
	temp = (char **)malloc((i) * sizeof(char *));
	i = 1;
	while (args[i] != NULL)
	{
		temp[i - 1] = ft_strdup(args[i]);
		i++;
	}
	temp[i - 1] = NULL;
	return (temp);
}

/**
 * Finds the type of redirection based on the given string.
 *
 * @param str The string to check for redirection.
 * @return The type of redirection found.
 */
int	find_redir(char *str)
{
	if (!ft_memcmp_ms(str, "|"))
		return (T_PIPE);
	else if (!ft_memcmp_ms(str, ">"))
		return (T_GREATER);
	else if (!ft_memcmp_ms(str, "<"))
		return (T_LESSER);
	else if (!ft_memcmp_ms(str, "<<"))
		return (T_HEREDOC);
	else if (!ft_memcmp_ms(str, ">>"))
		return (T_APPEND);
	else if (!ft_memcmp_ms(str, "<>"))
		return (T_MISTAKE);
	return (T_WORD);
}

/**
 * Compares two memory blocks.
 *
 * This function compares the memory blocks pointed to by `s1` and `s2`.
 * It returns an integer less than, equal to, or greater than zero if the
 *  first `n` bytes of `s1` are found,
 * respectively, to be less than, to match, or be greater 
 * than the first `n` bytes of `s2`.
 *
 * @param s1 A pointer to the first memory block to be compared.
 * @param s2 A pointer to the second memory block to be compared.
 * @return An integer less than, equal to, or greater than zero if the first 
 * `n` bytes of `s1` are found,
 * respectively, to be less than, to match, or be greater than the first
 *  `n` bytes of `s2`.
 */
int	ft_memcmp_ms(const void *s1, const void *s2)
{
	char	*p1;
	char	*p2;
	int		i;
	int		len;

	p1 = (char *)s1;
	p2 = (char *)s2;
	len = ft_strlen_ms(p1);
	i = 0;
	if (len != ft_strlen_ms(p2))
		return (-1);
	while (i < len)
	{
		if (p1[i] != p2[i])
		{
			return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}
