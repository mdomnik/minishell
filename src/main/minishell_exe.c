/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:01:19 by kaan              #+#    #+#             */
/*   Updated: 2024/03/22 15:17:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	handle_ctrlc(int sig)
{
	(void)sig;
	printf("\n");
	printf(CL_NAME);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;

	(void)argv;
	(void)envp;
	if (argc != 1)
		ft_exit("Excute the program without addtional argument\n");
	prompt = NULL;
	prompt = init_prompt(prompt);
	prompt->envp->env = double_dup(envp);
	if (!prompt->envp->env)
		simple_err(ERR_ENV);
	while (1)
	{
		//disable "ctrl-\"
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_exit("quit\n");
		//enable "ctrl-c"
		signal(SIGINT, handle_ctrlc);
		prompt->line = readline(CL_NAME);
		//enable "ctrl-d"
		if (!prompt->line)
			ft_exit("quit minishell");
		split_tokens(prompt);
		add_history(prompt->line);
	}
}
