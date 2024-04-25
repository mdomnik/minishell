/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:16:07 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/25 18:43:41 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Executes the built-in exit command.
 * 
 * This function is responsible for freeing allocated memory and resources,
 * printing an exit message, and terminating the program.
 * 
 * @param shell A pointer to the shell structure.
 */
void	builtin_exit(t_shell *shell)
{
	if (shell->env)
		free_double(shell->env);
	if (shell->line)
		free(shell->line);
	if (shell->lexer)
		lexerfreelist_ms(&shell->lexer);
	if (shell->expand)
		expandfreelist_ms(&shell->expand);
	if (shell->parser)
		parserfreelist_ms(&shell->parser);
	free(shell);
	printf("exit\n");
	exit(0);
}
