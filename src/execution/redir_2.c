/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:01:41 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/26 12:59:49 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**add_string(char **array, int *size, const char *new_string)
{
	char	**new_array;

	new_array = malloc((*size + 1) * sizeof(char *));
	if (new_array == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	array = add_string_util(new_array, array, size, new_string);
	(*size)++;
	return (array);
}

char	**add_string_util(char **n_arr, char **arr, int *s, const char *n_str)
{
	int		i;

	i = 0;
	while (i < *s)
	{
		n_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	n_arr[*s] = ft_strdup(n_str);
	free_double(arr);
	arr = malloc((*s + 2) * sizeof(char *));
	i = 0;
	while (i < *s + 1)
	{
		arr[i] = ft_strdup(n_arr[i]);
		i++;
	}
	i = 0;
	while (n_arr[i] != NULL && i < (*s))
	{
		free(n_arr[i]);
		i++;
	}
	free(n_arr);
	return (arr);
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
		heredoc(shell, exec);
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
		exec = return_exec(shell, exec);
	else if (!exec->next && (exec->operator == APPEND
			|| exec->operator == GREAT))
		exec->operator = NONE;
	else if (exec->operator == HEREDOC)
		exec->operator = NONE;
	if (exec->operator == NONE)
		exec_cmd(shell, exec);
	else
		pipe_exe(shell, exec);
}

t_exec	*return_exec(t_shell *shell, t_exec *exec)
{
	if (shell->in_fd != -1)
	{
		dup2(shell->in_fd, STDIN_FILENO);
		redir_output(shell, exec);
	}
	if (exec->next)
		exec->operator = PIPE;
	else
		exec->operator = NONE;
	return (exec);
}
