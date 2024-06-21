/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:20:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/21 13:49:59 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	less(t_exec *exec)
{
	int		fd;

	fd = 0;
	if (exec->next->token[0])
	{
		while (exec->operator == LESS)
		{
			exec->operator = NONE;
			if (access(exec->next->token[0], F_OK) == -1)
				less_nofile_exit();
			exec = exec->next;
		}
		while (exec->operator == LESS)
		{
			exec->operator = NONE;
			if (access(exec->next->token[0], F_OK) == -1)
				less_nofile_exit();
			exec = exec->next;
		}
		//ft_putnbr_fd(exec->token_count, 2);
		//perror(exec->token[0]);
		if (exec->token_count > 2
			&& exec->token[1])
			less_multi_file(exec, fd);
		else if (access(exec->token[0], F_OK) == 0)
			less_one_file(exec, fd);
		else if (pipe_check(exec) && redir_check(exec))
			less_invalid_input(exec->token[0]);
	}
}

void	heredoc(t_exec *exec)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (strcmp_msn(buff, exec->next->token[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
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

void	redir_output(t_exec *exec)
{
	close(STDOUT_FILENO);
	while (exec->next->operator == GREAT
		|| exec->next->operator == APPEND)
	{
		if (exec->operator == GREAT)
			ft_open(exec->next->token[0], O_TRUNC);
		else if (exec->operator == APPEND)
			ft_open(exec->next->token[0], O_APPEND);
		exec = exec->next;
		close(STDOUT_FILENO);
	}
	if (exec->operator == GREAT)
		ft_open(exec->next->token[0], O_TRUNC);
	else if (exec->operator == APPEND)
		ft_open(exec->next->token[0], O_APPEND);
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
	free_d_lst(array);
	array = malloc((*size + 2) * sizeof(char *));
	i = 0;
	while (i < *size + 1)
	{
		array[i] = ft_strdup(new_array[i]);
		i++;
	}
	i = 0;
	while (new_array[i] && i < *size + 1)
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
	t_exec *first;
	t_exec *third;
	int	size;
	int	i;

	first = exec;
	size = get_token_count_ms(first->token);
	i = 0;
	while (first->next->token[i])
	{
		first->token = add_string(first->token, &size, first->next->token[i]);
		i++;
	}
	first->token[i + 1] = NULL;
	first->operator = first->next->operator;
	free_d_lst(first->next->token);
	free(first->next);
	if (exec->next->next)
		third = exec->next->next;
	else
		third = NULL;
	first->next = third;
	return (first);
}

void	redir_exe(t_shell *shell, t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	if (exec->operator == LESS)
		less(exec);
	else if (exec->operator == HEREDOC)
		heredoc(exec);
	else
		redir_output(exec);
	//print_exec(temp);
	temp->operator = NONE;
	if (pipe_check(temp) || redir_check(temp))
		temp = cat_exec(temp);
	//print_exec(temp);
	//print_token(temp->token);
	/*while (exec->operator != NONE && exec->operator != PIPE)
		exec = exec->next;*/
	if (exec->operator == NONE)
		exec_cmd(shell, temp);
	else
		pipe_exe(shell, exec);
}
