/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/04 17:37:11 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Fork and execute command
void	single_cmd_exe(t_shell *shell)
{
	pid_t		pid;
	t_parser	*current;
	int			input_fd;
	int			output_fd;
	//int			status;

	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	current = shell->parser;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		set_signals_child();
		if (input_fd != STDIN_FILENO)
		{
			if (dup2(input_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 input_fd");
				exit(EXIT_FAILURE);
			}
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			if (dup2(output_fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 output_fd");
				exit(EXIT_FAILURE);
			}
			close(output_fd);
		}
		if (find_path(shell) == 1)
			exit(EXIT_SUCCESS);
		proc_termination(shell);
	}
	//waitpid(-1, &status, 0);
	wait_processes(shell);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
	{
		close(output_fd);
	}
	reset_loop(shell, NULL, shell->parser->cmd, 0);
}

/**
 * Take output from parser and executes it. The final part of the shell.
 *
 * @param shell The shell structure containing the parsed command.
 */

void	execute(t_shell *shell)
{
	//print_parser(shell);
	shell->pid = -2;
	if (shell->parser->output == T_PIPE
		|| shell->parser->output == T_GREATER
		|| shell->parser->output == T_APPEND
		|| shell->parser->input == T_LESSER
		|| shell->parser->input == T_HEREDOC)
		pipex(shell);
	else if (shell->parser->cmd != NULL && shell->parser->output != 1)
		find_builtin(shell);
	else
		reset_loop(shell, ERR_NUM, shell->parser->cmd, 0);
}

/* Finds and executes the appropriate built-in
 * command based on the given command.
 * If the command is not a built-in command, 
 * it attempts to find the command in the system's PATH.
 * If the command is not found, an error message is printed.
 *
 * @param shell The shell structure containing the parsed 
 * command and other shell data.
 */
int	find_builtin(t_shell *shell)
{
	char	*cmd;

	//printf("pid_error:%d\n", shell->pid);
	cmd = shell->parser->cmd;
	if (cmp_str(cmd, "echo") == 0)
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
	else if (cmp_str(cmd, "cd") == 0)
		builtin_cd(shell);
	else
		single_cmd_exe(shell);
	if (shell->pid != -2)
	{
		perror("error!");
		proc_termination(shell);
	}
	reset_loop(shell, NULL, shell->parser->cmd, 0);
	return (1);
}
