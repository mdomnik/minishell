/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:59:37 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/29 21:04:54 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Executes the built-in echo command.
 *
 * This function prints the arguments passed to the echo command.
 * If the '-n' option is not provided, a newline character is printed at the end.
 *
 * @param shell The shell structure.
 */
void	builtin_echo(t_shell *shell)
{
	int	n_flag_value;
	int	*n_flag;
	int	i;

	n_flag_value = 0;
	n_flag = &n_flag_value;
	i = check_echo_option(shell->parser->args, &n_flag, 0);
	while (shell->parser->args[i])
	{
		printf("%s", shell->parser->args[i]);
		if (shell->parser->args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag_value == 0)
		printf("\n");
	// reset_loop(shell, NULL);
}

/**
 * Checks the echo options in the given arguments array.
 * returns the index of the first argument that is not an option.
 * 
 * @param args The array of arguments.
 * @param n_flag A pointer to the integer flag for the '-n' option.
 * @param i The current index in the arguments array.
 * @return The index of the first argument that is not an option, or the index
 *  of the last argument if all are options.
 */
int	check_echo_option(char **args, int **n_flag, int i)
{
	while (args[i] != NULL)
	{
		if (args[i][0] == '-')
		{
			if (find_if_n(args[i]) == 1)
				**n_flag = 1;
			else
				return (i);
		}
		else
			return (i);
		i++;
	}
	**n_flag = 1;
	return (i);
}

/**
 * @brief Checks if the given string contains the character 'n'
 * and returns 1 if found, 0 otherwise.
 * 
 * @param str The string to check.
 * @return int Returns 1 if 'n' is found in the string, 0 otherwise.
 */
int	find_if_n(char *str)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 'n' && str[i] != 'e' && str[i] != 'E')
			n_flag = 2;
		if (str[i] == 'n' && n_flag == 0)
			n_flag = 1;
		i++;
	}
	if (n_flag == 1)
		return (1);
	return (0);
}
