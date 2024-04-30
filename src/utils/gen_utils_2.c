/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:28:06 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/30 21:27:38 by mdomnik          ###   ########.fr       */
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

/**
 * Appends the command at the front of the argument array.
 * 
 * @param shell The shell structure.
 * @param args The argument array.
 * @return The updated argument array with the command appended at the front,
 *         or NULL if memory allocation fails.
 */
char	**append_cmd_front(t_shell *shell, char **args)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (count_args(args) + 2));
	if (!copy)
		return (NULL);
	copy[0] = ft_strdup(shell->parser->cmd);
	while (args[i] != NULL)
	{
		copy[i + 1] = ft_strdup(args[i]);
		if (!copy[i])
		{
			free_double(copy);
			return (NULL);
		}
		i++;
	}
	copy[i + 1] = NULL;
	free_double(args);
	return (copy);
}

/**
 * Compares two strings.
 *
 * This function compares the string pointed to by `s1`
 *  to the string pointed to by `s2`.
 * The comparison is done character by character, until
 * a difference is found or one of the strings ends.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return 0 if the strings are equal, 1 otherwise.
 */
int	strcmp_ms(char *s1, char *s2)
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
 * Prepares and declares variables in the shell structure.
 * Sorts the variables and adds quotes to their values.
 *
 * @param shell The shell structure.
 */
void	prep_declare(t_shell *shell)
{
	int	i;

	i = 0;
	sort_declare(shell);
	while (shell->declare[i])
	{
		shell->declare[i] = add_value_quotes(shell->declare[i], 1);
		if (!shell->declare[i])
			free_err(ERR_MALLOC, shell);
		i++;
	}
}
