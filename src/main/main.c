/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:27:52 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/25 15:28:05 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function runs at launch:
user should start the shell program using just
"./minishell" with no other arguments. If
arguments are given, return error. else, 
main initializes components of s_shell struct,
copies all environmental variables to shell->env
and starts the core loop ("shell_loop") */
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = NULL;
	if (argc != 1 || argv[1])
		simple_err(ERR_I);
	shell = init_shell(shell);
	if (shell == NULL)
		simple_err(ERR_SHELL);
	shell->env = double_dup(envp);
	if (!shell->env)
		free_err(ERR_ENV, shell);
	shell->declare = double_dup(envp);
	if (!shell->declare)
		free_err(ERR_ENV, shell);
	prep_declare(shell);
	rl_clear_history();
	shell_loop(shell);
	return (0);
}

/* core loop of the shell
    waits for input from user, then
    sends it for processing */
void	shell_loop(t_shell *shell)
{
	config_signals();
	shell->line = readline(CL_NAME);
	if (!shell->line) 
	{
		if (shell->declare)
			free_double(shell->declare);
		if (shell->env)
			free_double(shell->env);
		if (shell->exit_status)
			free(shell->exit_status);
		free(shell);
		printf("exit\n");
		exit(0);
	}
	if (shell->line[0] != '\0')
	{
		add_history(shell->line);
		tokenizer(shell, 0, 1);
	}
	if (shell->line)
		free(shell->line);
	shell_loop(shell);
}

/**
 * Resets the loop by freeing the memory allocated for the shell's line
 * and then calls the shell_loop function.
 *
 * @param shell A pointer to the t_shell struct representing the shell.
 */
void	reset_loop(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->lexer)
		lexerfreelist_ms(&shell->lexer);
	if (shell->expand)
		expandfreelist_ms(&shell->expand);
	if (shell->exec)
		execfreelist_ms(&shell->exec);
	shell->expand = NULL;
	shell->lexer = NULL;
	shell->parser = NULL;
	shell->exec = NULL;
	shell->in_fd = -1;
	shell->out_fd = -1;
	shell_loop(shell);
}

/* this function initializes all components
   of the shell struct, including all other
   stucts, of which, reference is held in 
	this instance of t_shell. Additionally,
	it checks for allocation failures and
	frees accordingly*/
t_shell	*init_shell(t_shell *shell)
{
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->expand = NULL;
	shell->lexer = NULL;
	shell->parser = NULL;
	shell->exec = NULL;
	shell->env = NULL;
	shell->declare = NULL;
	shell->exit_status = malloc(sizeof(int));
	*(shell->exit_status) = 0;
	shell->in_fd = -1;
	shell->out_fd = -1;
	return (shell);
}
