/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:27:52 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/20 17:37:18 by mdomnik          ###   ########.fr       */
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
	shell_loop(shell);
	return (0);
}

/* core loop of the shell
    waits for input from user, then
    sends it for processing*/

void	shell_loop(t_shell *shell)
{
	shell->line = readline(CL_NAME);
	if (shell->line[0] != '\0')
	{
		tokenizer(shell);
		add_history(shell->line);
	}
	if (shell->line)
	{
		free(shell->line);
		shell_loop(shell);
	}
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
	return (shell);
}
