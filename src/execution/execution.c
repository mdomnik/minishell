/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/25 18:13:21 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Take output from parser and executes it. The final part of the shell.
 *
 * @param shell The shell structure containing the parsed command.
 */
void	execute(t_shell *shell)
{
	// print_parser(shell);
	find_builtin(shell);
}

void find_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->parser->cmd, "pwd", ft_strlen(shell->parser->cmd)) == 0)
		pwd(shell);
	else
		reset_loop(shell, ERR_CMD);
}

// void find_builtin(t_shell *shell)
// {
// 	if (ft_strcmp(shell->parser->cmd, "pwd") == 0)
// 		pwd(shell);
// 	else if (ft_strcmp(shell->parser->cmd, "echo") == 0)
// 		echo(shell);
// 	else if (ft_strcmp(shell->parser->cmd, "cd") == 0)
// 		cd(shell);
// 	else if (ft_strcmp(shell->parser->cmd, "export") == 0)
// 		export(shell);
// 	else if (ft_strcmp(shell->parser->cmd, "unset") == 0)
// 		unset(shell);
// 	else if (ft_strcmp(shell->parser->cmd, "env") == 0)
// 		env(shell);
// 	else if (ft_strcmp(shell->parser->cmd, "exit") == 0)
// 		exit_builtin(shell);
// 	else
// 	{
// 		shell->parser->cmd_path = find_path(shell);
// 		if (shell->parser->cmd_path)
// 			execve(shell->parser->cmd_path, shell->parser->args, shell->env);
// 		else
// 			reset_loop(shell, ERR_CMD);
// 	}
// }
