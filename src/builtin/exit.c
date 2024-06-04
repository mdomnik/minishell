/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:16:07 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/04 17:21:33 by mdomnik          ###   ########.fr       */
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
	int exit_code;

	exit_code = 0;
	if (count_args(shell->parser->args) > 1)
	{
		reset_loop(shell, ERR_ARG, shell->parser->cmd, 1);
		return ;
	}
	else if (count_args(shell->parser->args) == 1)
	{
		if (ft_isnum(shell->parser->args[0]) == 0)
		{
			reset_loop(shell, ERR_NUM, shell->parser->cmd, 2);
			return ;
		}
		exit_code = get_exit(ft_atoi(shell->parser->args[0]));
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
			return (0);
		i++;
	}
	return (1);
}
