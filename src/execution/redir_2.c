/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:01:41 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 19:26:08 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_output(t_shell *shell, t_exec *exec)
{
	close(STDOUT_FILENO);
	remove_output_node(shell, exec);
	if (exec->operator == GREAT)
	{
		perror("last great");
		ft_open(exec->next->token[0], O_TRUNC);
		remove_exec_node_at_index(shell, exec->next->index);
	}
	else if (exec->operator == APPEND)
	{
		perror("last apennd");
		ft_open(exec->next->token[0], O_APPEND);
		remove_exec_node_at_index(shell, exec->next->index);
	}
}

char	**add_string(char **array, int *size, const char *new_string)
{
	char	**new_array;
	int		i;

	new_array = malloc((*size + 1) * sizeof(char *));
	if (new_array == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < *size)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[*size] = ft_strdup(new_string);
	free_double(array);
	array = malloc((*size + 2) * sizeof(char *));
	i = 0;
	while (i < *size + 1)
	{
		array[i] = ft_strdup(new_array[i]);
		i++;
	}
	i = 0;
	while (new_array[i] != NULL && i < (*size))
	{
		free(new_array[i]);
		i++;
	}
	free(new_array);
	(*size)++;
	return (array);
}

t_exec	*cat_exec(t_exec *exec)
{
	t_exec	*first;
	t_exec	*third;
	int		i;

	first = exec;
	i = 0;
	while (first->next->token[i])
	{
		first->token = add_string(first->token, &(first->token_count),
				first->next->token[i]);
		i++;
	}
	first->token[i + 1] = NULL;
	first->operator = first->next->operator;
	if (exec->next->next)
		third = exec->next->next;
	else
		third = NULL;
	free_double(first->next->token);
	free(first->next);
	first->next = third;
	return (first);
}

void	redir_exe(t_shell *shell, t_exec *exec)
{
	if (exec->operator == LESS)
		less(shell, exec);
	else if (exec->operator == HEREDOC)
		heredoc(exec);
	else
		redir_output(shell, exec);
	if (exec->next && exec->operator == LESS)
	{
		exec->operator = NONE;
		exec = cat_exec(exec);
	}
	else if (!exec->next && (exec->operator == LESS))
		exec->operator = NONE;
	else if (exec->next && (exec->operator == APPEND
			|| exec->operator == GREAT))
			{
				redir_output(shell, exec);
				exec->operator = PIPE;
			}
	else if (!exec->next && (exec->operator == APPEND
			|| exec->operator == GREAT))
		exec->operator = NONE;
	if (exec->operator == NONE)
		exec_cmd(shell, exec);
	else
		pipe_exe(shell, exec);
}
