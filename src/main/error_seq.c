/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_seq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:19:13 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/03 20:09:32 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints the given error string and exits the program with a status of 1.
 *
 * @param err_str The error string to be printed.
 */
void	simple_err(char *err_str)
{
	printf("%s\n", err_str);
	exit(1);
}

/**
 * Frees shell structure and prints the error message,
 * and exits the program with a status of 1.
 *
 * @param err_str The error message string to be printed.
 * @param shell   The shell structure to be freed.
 */
void	free_err(char *err_str, t_shell *shell)
{
	perror(err_str);
	free_shell(shell);
	exit(1);
}
void ft_perror(const char *msg, char *cmd, unsigned int err, t_shell *shell)
{
	if (msg != NULL)
		write(2, msg, ft_strlen(msg));
	else if (cmd != NULL)
	{
		write(2, ": ", 2);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
	}
	*(shell->exit_status) = err;
	return ;
}

/**
 * Frees the memory allocated for a shell structure.
 * 
 * @param shell The shell structure to free.
 */
void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_double(shell->env);
	if (shell->declare)
		free_double(shell->declare);
	if (shell->line)
		free(shell->line);
	if (shell->lexer)
		lexerfreelist_ms(&shell->lexer);
	if (shell->expand)
		expandfreelist_ms(&shell->expand);
	if (shell->parser)
		parserfreelist_ms(&shell->parser);
	if (shell->last_dir)
		free(shell->last_dir);
	if (shell->exit_status)
		free(shell->exit_status);
	free(shell);
}
