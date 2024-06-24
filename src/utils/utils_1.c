/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:41:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 17:51:54 by mdomnik          ###   ########.fr       */
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
		return (double_dollar (str));
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

char	**double_dollar(char *str)
{
	char	**ret;
	char	*temp;
	char	*pid;
	int		i;

	pid = ft_itoa(getpid());
	i = 0;
	ret = (char **)malloc(2 * sizeof(char *));
	if (!ret)
		return (NULL);
	while (str[i] == '$')
		i++;
	temp = ft_substr(str, i, ft_strlen(str) - i);
	ret[0] = NULL;
	i = i / 2;
	while (i > 0)
	{
		ret[0] = ft_strjoin(ret[0], pid);
		i--;
	}
	if (!ret[0])
		ret[0] = ft_strjoin_ms(pid, temp);
	else
		ret[0] = ft_strjoin(ret[0], temp);
	ret[1] = NULL;
	return (ret);
}
