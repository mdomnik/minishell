/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:28:06 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/26 01:18:03 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Compares two strings.
 *
 * This function compares the strings `s1` and `s2` character by character until
 * a difference is found or one of the strings ends. If both strings are equal,
 * the function returns 0. Otherwise, it returns 1.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return 0 if the strings are equal, 1 otherwise.
 */
int	cmp_str(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}

/**
 * Counts the number of arguments in an array of strings.
 *
 * @param args The array of strings representing the arguments.
 * @return The number of arguments in the array.
 */
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**double_join(char *str, t_shell *shell)
{
	char	**new_duostr;
	int		i;

	i = 0;
	new_duostr = (char **)malloc((count_args(shell->env) + 1) * sizeof(char *));
	if (!new_duostr)
		free_err(ERR_MALLOC, shell);
	while (i <= count_args(shell->env))
	{
		new_duostr[i] = ft_strdup(shell->env[i]);
		if (!new_duostr[i])
			free_err(ERR_MALLOC, shell);
		i++;
	}
	free_double(shell->env);
	return (new_duostr);
}
