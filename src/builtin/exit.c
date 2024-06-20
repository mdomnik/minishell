/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:16:07 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/20 16:30:16 by mdomnik          ###   ########.fr       */
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
void	builtin_exit(t_shell *shell, t_exec *exec)
{
	int exit_code;

	exit_code = 0;
	if (exec->token_count > 2)
		exit(EXIT_FAILURE);
	else if (exec->token_count == 2)
	{
		if (ft_isnum(exec->token[1]) == 1)
		{
			exit(EXIT_FAILURE);
		}
		exit_code = get_exit(ft_atoi(exec->token[1]));
		*(shell->exit_status) = exit_code;
	}
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
	if (shell->exec)
		execfreelist_ms(&shell->exec);
	free(shell);
	printf("exit\n");
	exit(exit_code);
}

int get_exit(int exit_code)
{
	if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	else if (exit_code > 255)
		exit_code = exit_code % 256;
	return (exit_code);
}

int ft_isnum(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
