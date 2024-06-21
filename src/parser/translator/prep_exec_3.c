/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:10:07 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/21 15:13:00 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void remove_non_exist_input(t_shell *shell)
{
	t_exec	*exec;
	int		i;

	exec = shell->exec;
	i = 0;
	while(exec != NULL)
	{
		i++;
		if (exec->operator == LESS && access(exec->next->token[0], F_OK) == -1)
		{
			*(shell->exit_status) = 1;
			ft_putendl_fd(NO_FILE, 2);
			purge_till_input(shell, i);
		}
		exec = exec->next;
	}
}

void purge_till_input(t_shell *shell, int i)
{
	t_exec	*exec;
	t_exec	*temp;
	
	
	exec = shell->exec;
	while(exec->next != NULL && i > 0)
	{
		temp = exec->next;
		free_double(exec->token);
		free(exec);
		exec = temp;
		i--;
	}
	if (exec->operator == NONE)
	{
		shell->exec = exec;
		execfreelist_ms(&shell->exec);
		return ;
	}
	else if (exec->operator == PIPE)
	{
		temp = exec->next;
		free_double(exec->token);
		free(exec);
		exec = temp;
	}
	shell->exec = exec;
}

void check_file_existance(t_shell *shell)
{
	t_parser	*parser;
	int			i;
	int			fd;

	parser = shell->parser;
	while(parser != NULL)
	{
		i = 0;
		while(parser->files[i] != NULL)
		{
			if (parser->file_types[i] == 2)
			{
				fd = open(parser->files[i], O_WRONLY | O_TRUNC | O_CREAT, 0666);
				if (fd == -1)
				{
					perror(" ");
					*(shell->exit_status) = 1;
					reset_loop(shell);
				}
				close(fd);				
			}
			i++;
		}
		parser = parser->next;
	}
	
}