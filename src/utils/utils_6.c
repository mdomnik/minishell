/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:00:23 by kaan              #+#    #+#             */
/*   Updated: 2024/06/24 15:45:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Exits the shell with a given exit status and prints an optional error message.
 *
 * @param shell The shell structure.
 * @param msg The error message to be printed (optional).
 * @param exit_status The exit status of the shell.
 */
void	exit_shell(t_shell *shell, char *msg, int exit_status)
{
	(void)shell;
	if (shell)
		free_shell(shell);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}

/**
 * Compares two strings and checks if they are equal.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return true if the strings are equal, false otherwise.
 */
bool	strcmp_msn(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((s1 && !s2) || (!s1 && s2))
		return (false);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (true);
	return (false);
}

/**
 * Prints an error message indicating that the given variable
 * name is not a valid identifier.
 *
 * @param var_name The name of the invalid variable.
 */
void	invalid_identifer(char *var_name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(var_name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

/**
 * Checks if the given token is unexpected and prints an error message.
 *
 * @param token The token to check.
 * @return true if the token is unexpected, false otherwise.
 */
bool	unexpected_token(char token)
{
	ft_putstr_fd("UNEXPECTED_TOKEN", STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (true);
}

/**
 * Checks if a string represents a valid number.
 *
 * @param str The string to be checked.
 * @return true if the string represents a valid number, false otherwise.
 */
bool	ft_isnum_bool(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
