/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:20:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/26 12:59:14 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_less(t_shell *shell, t_exec *exec)
{
	t_exec	*current;
	t_exec	*next_node;

	current = exec;
	while (current->next != NULL && current->next->operator == LESS)
	{
		next_node = current->next;
		if (access(exec->next->token[0], F_OK | R_OK) == -1)
			return ;
		remove_exec_node_at_index(shell, next_node->index);
		current = next_node;
	}
}

void	less(t_shell *shell, t_exec *exec)
{
	if (exec->next->token[0])
	{
		remove_less(shell, exec);
		if (access(exec->next->token[0], F_OK | R_OK) == 0)
		{
			shell->in_fd = open(exec->next->token[0], O_RDONLY, 0666);
			exec->operator = exec->next->operator;
			remove_exec_node_at_index(shell, exec->next->index);
			dup2(shell->in_fd, STDIN_FILENO);
		}
		else
		{
			ft_putendl_fd(NO_FILE, 3);
			dup2(3, STDIN_FILENO);
		}
	}
}

void	heredoc(t_shell *shell, t_exec *exec)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	set_signals_child();
	while (1)
	{
		buff = readline("> ");
		if (strcmp_msn(buff, exec->next->token[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	exec->operator = exec->next->operator;
	remove_exec_node_at_index(shell, exec->next->index);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

void	ft_open(char *token, int option)
{
	if (open(token, O_WRONLY | option | O_CREAT, 0666) == -1)
	{
		perror(" ");
		exit(EXIT_FAILURE);
	}
}

void	remove_output_node(t_shell *shell, t_exec *exec)
{
	t_exec	*current;
	t_exec	*next_node;

	current = exec;
	while (current->next != NULL
		&& (current->next->operator == GREAT
			|| current->next->operator == APPEND))
	{
		next_node = current->next;
		if (current->operator == GREAT)
		{
			ft_open(next_node->token[0], O_TRUNC);
			current->operator = next_node->operator;
			remove_exec_node_at_index(shell, next_node->index);
		}
		else if (current->operator == APPEND)
		{
			ft_open(next_node->token[0], O_APPEND);
			current->operator = next_node->operator;
			remove_exec_node_at_index(shell, next_node->index);
		}
		current = next_node;
		close(STDOUT_FILENO);
	}
}
