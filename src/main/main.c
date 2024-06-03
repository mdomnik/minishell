/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:27:52 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/01 17:48:54 by kaan             ###   ########.fr       */
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
	starting_dir(shell);
	rl_clear_history();
	shell_loop(shell);
	return (0);
}

/* core loop of the shell
    waits for input from user, then
    sends it for processing */

void	shell_loop(t_shell *shell)
{
	set_signals();
	shell->line = readline(CL_NAME);
	if (!shell->line) 
	{
		if (shell->declare)
			free_double(shell->declare);
		if (shell->env)
			free_double(shell->env);
		if (shell->last_dir)
			free(shell->last_dir);
		if (shell->exit_status)
			free(shell->exit_status);
		free(shell);
		printf("exit\n");
		exit(0);
	}
	if (shell->line[0] != '\0')
	{
		add_history(shell->line);
		tokenizer(shell);
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
void	reset_loop(t_shell *shell, char *msg)
{
	if (msg)
		printf("%s\n", msg);
	if (shell->line)
		free(shell->line);
	if (shell->lexer)
		lexerfreelist_ms(&shell->lexer);
	if (shell->expand)
		expandfreelist_ms(&shell->expand);
	if (shell->parser)
		parserfreelist_ms(&shell->parser);
	if (shell->cmd_count)
		free(shell->cmd_count);
	shell->expand = NULL;
	shell->lexer = NULL;
	shell->parser = NULL;
	shell->cmd_count = NULL;
	reset_increment_k(0);
	if (shell->pid == 0)
		exit(1);
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
	shell->env = NULL;
	shell->declare = NULL;
	shell->last_dir = NULL;
	shell->exit_status = malloc(sizeof(int));
	*(shell->exit_status) = 0;
	shell->pid = -1;
	return (shell);
}

void	starting_dir(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		free_err(ERR_PWD, shell);
	shell->last_dir = ft_strdup(cwd);
	if (shell->last_dir == NULL)
		free_err(ERR_MALLOC, shell);
	free(cwd);
}
