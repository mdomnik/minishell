/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:54:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/05/29 22:53:16 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Take output from parser and executes it. The final part of the shell.
 *
 * @param shell The shell structure containing the parsed command.
 */

void handle_here_document(const char *delimiter, int *input_fd) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int temp_fd = open("/tmp/heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (temp_fd == -1) {
        perror("open temp file");
        exit(EXIT_FAILURE);
    }

    printf("heredoc> ");
    while ((read = getline(&line, &len, stdin)) != -1) {
        if (strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\n') {
            break;
        }
        write(temp_fd, line, read);
        printf("heredoc> ");
    }

    free(line);
    close(temp_fd);

    *input_fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (*input_fd == -1) {
        perror("open temp file for read");
        exit(EXIT_FAILURE);
    }
}

void execute(t_shell *shell) {
    t_parser *current;
    pid_t pid;
    int input_fd = STDIN_FILENO;
    int pipefd[2];
    int status;
    int is_pipe = 0;

    current = shell->parser;

    while (current != NULL) {
        int output_fd = STDOUT_FILENO;

        // Check if the next command needs a pipe
        if (current->output == T_PIPE) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            output_fd = pipefd[1];
            is_pipe = 1;
        } else if (current->output == T_GREATER || current->output == T_APPEND) {
            if (current->output == T_APPEND) {
                output_fd = open(current->o_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                output_fd = open(current->o_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (output_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        }

        // Set up input redirection
        if (current->input == T_PIPE) {
            input_fd = pipefd[0];
        } else if (current->input == T_LESSER) {
            input_fd = open(current->i_str, O_RDONLY);
            if (input_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        } else if (current->input == T_HEREDOC) {
            handle_here_document(current->i_str, &input_fd);
        }

        // Fork and execute command
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) { // Child process
            if (input_fd != STDIN_FILENO) {
                if (dup2(input_fd, STDIN_FILENO) == -1) {
                    perror("dup2 input_fd");
                    exit(EXIT_FAILURE);
                }
                close(input_fd);
            }
            if (output_fd != STDOUT_FILENO) {
                if (dup2(output_fd, STDOUT_FILENO) == -1) {
                    perror("dup2 output_fd");
                    exit(EXIT_FAILURE);
                }
                close(output_fd);
            }
            // Execute the command
            if (find_builtin(shell) == 1) { // If it's a built-in command
                exit(EXIT_SUCCESS); // Exit child process
            } else {
                execvp(current->cmd, current->args);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
        }

        // Parent process
        if (input_fd != STDIN_FILENO && current->input == T_LESSER) {
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO && current->output != T_PIPE) {
            close(output_fd);
        }

        if (is_pipe) {
            close(pipefd[1]);     // Close the write end of the pipe in the parent
            input_fd = pipefd[0]; // Set up the input for the next command
            is_pipe = 0;
        } else {
            input_fd = STDIN_FILENO;
        }

        current = current->next;
    }

    // Wait for all child processes to complete
    while ((pid = wait(&status)) > 0);

    // Explicitly restore standard input/output in the parent process
    dup2(STDIN_FILENO, 0);
    dup2(STDOUT_FILENO, 1);
    dup2(STDERR_FILENO, 2);

    reset_loop(shell, NULL); // Reset the shell state if needed
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
		return(0);
		reset_loop(shell, NULL);
	}
	return (1);
}
