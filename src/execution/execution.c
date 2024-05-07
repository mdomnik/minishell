/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/07 15:26:21 by mdomnik          ###   ########.fr       */
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
	find_builtin(shell);
}

/**
 * Finds and executes the appropriate built-in
 * command based on the given command.
 * If the command is not a built-in command, 
 * it attempts to find the command in the system's PATH.
 * If the command is not found, an error message is printed.
 *
 * @param shell The shell structure containing the parsed 
 * command and other shell data.
 */
void	find_builtin(t_shell *shell)
{
	char	*cmd;

	cmd = shell->parser->cmd;
	if (cmp_str(cmd, "cd") == 0)
		builtin_cd(shell);
	else if (cmp_str(cmd, "echo") == 0)
		builtin_echo(shell);
	else if (cmp_str(cmd, "env") == 0)
		builtin_env(shell);
	else if (cmp_str(cmd, "exit") == 0)
		builtin_exit(shell);
	else if (cmp_str(cmd, "export") == 0)
		builtin_export(shell);
	else if (cmp_str(cmd, "pwd") == 0)
		builtin_pwd(shell);
	else if (cmp_str(cmd, "unset") == 0)
		builtin_unset(shell);
	else
	{
		if (find_path(shell) != 0)
			printf("%s%s\n", shell->parser->cmd, ERR_NCMD);
		reset_loop(shell, NULL);
	}
}
