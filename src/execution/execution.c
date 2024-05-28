/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/27 13:49:59 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	great(t_shell *shell)
{
	int		fd;
	char	*file;

	file = *(shell->parser->files);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
        perror("Open Error");
		return ;
	}
	close(fd);
	reset_loop(shell, NULL);
}

/**
 * Take output from parser and executes it. The final part of the shell.
 *
 * @param shell The shell structure containing the parsed command.
 */
void	execute(t_shell *shell)
{
	//print_parser(shell);
	if (cmp_str(shell->parser->o_str, "PIPE") == 0)
        pipex(shell);
	else if (shell->parser->cmd != NULL && shell->parser->output != 1)
		find_builtin(shell);
	else
		reset_loop(shell, NULL);
}

void	operator_exe(t_shell *shell)
{
	if (shell->parser->output == 2)
		great(shell);
	else
		reset_loop(shell, NULL);
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
	else if (shell->parser->output == 2)
		operator_exe(shell);
	else
	{
		if (find_path(shell) != 0)
			printf("%s%s\n", shell->parser->cmd, ERR_NCMD);
		reset_loop(shell, NULL);
	}
}
