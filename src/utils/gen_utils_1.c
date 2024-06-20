/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:41:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/20 19:04:10 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Duplicates a double null-terminated string array.
 *
 * This function takes a double null-terminated string array
 * and creates a deep copy of it.
 * It allocates memory for the new array and duplicates each 
 * string element using ft_strdup.
 * If any memory allocation fails, it frees the previously 
 * allocated memory and returns NULL.
 *
 * @param str The double null-terminated string array to be duplicated.
 * @return A new double null-terminated string array that is a 
 * deep copy of the input array,
 *         or NULL if any memory allocation fails.
 */
char	**double_dup(char **str)
{
	int		i;
	char	**ret;

	i = 0;
	while (str[i] != NULL)
		i++;
	ret = (char **)malloc((i + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		ret[i] = ft_strdup(str[i]);
		if (ret[i] == NULL)
		{
			free_double(ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * Frees the memory allocated for a double string array.
 *
 * @param double_str The double string array to be freed.
 */
void	free_double(char **double_str)
{
	int	i;

	i = 0;
	if (double_str == NULL)
		return ;
	while (double_str[i] != NULL)
	{
		free(double_str[i]);
		i++;
	}
	free(double_str);
}

/**
 * Calculates the length of a string.
 *
 * @param s The string to calculate the length of.
 * @return The length of the string.
 */
int	ft_strlen_ms(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * Splits a string by a delimiter and adds the 
 * delimiter to each split element except the first one.
 * first element is checked for '$' and if it is present,
 *  it is added to the first element.
 * @param str The string to be split.
 * @return An array of strings where each element is a split
 *  part of the original string.
 */
char	**add_delim_split(char *str, t_shell *shell)
{
	int		i;
	int		is_env;
	char	**ret;

	i = 0;
	if (str[0] == '$')
		is_env = 1;
	else
		is_env = 0;
	if (str[0] == '$' && str[1] == '$')
	{
		ret = (char **)malloc(2 * sizeof(char *));
		if (!ret)
			return (NULL);
		ret[0] = ft_strdup("201088");
		ret[1] = NULL;
		return (ret);
	}
	if (str[0] == '$' && str[1] == '\0')
	{
		ret = (char **)malloc(2 * sizeof(char *));
		if (!ret)
			return (NULL);
		ret[0] = ft_strdup("$");
		ret[1] = NULL;
		return (ret);
	}
	ret = ft_split_ms(str, '$');
	if (ret[0] == NULL)
	{
		free_double(ret);
		ft_perror(ERR_CMD, NULL, 258, shell);
	}
	while (ret[i] != NULL)
	{
		if (i > 0)
			ret[i] = ft_strjoin_ms("$", ret[i]);
		i++;
	}
	if (is_env == 1)
		ret[0] = ft_strjoin_ms("$", ret[0]);
	return (ret);
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
