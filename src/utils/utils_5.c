/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:38:32 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/20 20:38:36 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	word_array(int word, const char *s, char c, char **ret);
static int	word_length(int word, char *s, char c);
static int	word_count(const char *s, char c);
static void	*freemal(char **strs, int count);

/**
 * Splits a string into an array of substrings based on a delimiter character.
 *
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return An array of substrings.
 */
char	**ft_split_ms(const char *s, char c)
{
	char	**ret;
	int		cells;

	cells = 0;
	if (!s)
	{
		ret = (char **)malloc(1);
		ret[0] = NULL;
		return (ret);
	}
	ret = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (cells < (word_count(s, c)))
	{
		word_array((cells + 1), (char *)s, c, ret);
		if (!ret[cells])
			return (freemal(ret, cells));
		cells++;
	}
	ret[cells] = NULL;
	return (ret);
}

static void	word_array(int w, const char *s, char c, char **ret)
{
	int		i;
	int		j;
	int		count;
	int		booly;

	i = 0;
	j = 0;
	count = 0;
	booly = 0;
	ret[w - 1] = (char *)malloc((word_length(w, (char *)s, c) + 1));
	if (!ret[w - 1])
		return ;
	while (s[i])
	{
		if (s[i] == c)
			booly = 0;
		if (booly == 0 && s[i] != c)
			count++;
		if (s[i] != c && count == w)
			ret[w -1][j++] = s[i];
		if (s[i] != c)
			booly++;
		i++;
	}
	ret[w - 1][j] = '\0';
}

static int	word_length(int word, char *s, char c)
{
	int		i;
	int		j;
	int		count;
	int		booly;

	i = 0;
	j = 0;
	count = 0;
	booly = 0;
	while (s[i])
	{
		if (s[i] == c)
			booly = 0;
		if (s[i] != c)
		{
			if (booly == 0)
				count++;
			if (count == word)
				j++;
			booly++;
		}
		i++;
	}
	return (j);
}

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;
	int	booly;

	i = 0;
	count = 0;
	booly = 0;
	while (s[i])
	{
		if (s[i] == c)
			booly = 0;
		if (s[i] != c)
		{
			if (booly == 0)
				count++;
			booly++;
		}
		i++;
	}
	return (count);
}

static void	*freemal(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}
