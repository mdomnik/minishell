/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:20:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/24 15:50:29 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

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
	int		in_file;

	if (exec->next->token[0])
	{
		remove_less(shell, exec);
		if (access(exec->next->token[0], F_OK | R_OK) == 0)
		{
			in_file = open(exec->next->token[0], O_RDONLY, 0666);
			remove_exec_node_at_index(shell, exec->next->index);
			dup2(in_file, STDIN_FILENO);
		}
		else
		{
			ft_putendl_fd(NO_FILE, 3);
			//remove_exec_node_at_index(shell, exec->next->index);
			dup2(3, STDIN_FILENO);
			//exit(EXIT_FAILURE);
		}
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
			perror("GREAT");
			ft_open(next_node->token[0], O_TRUNC);
			current->operator = next_node->operator;
			remove_exec_node_at_index(shell, next_node->index);
		}
		else if (current->operator == APPEND)
		{
			perror("append");
			ft_open(next_node->token[0], O_APPEND);
			current->operator = next_node->operator;
			remove_exec_node_at_index(shell, next_node->index);
		}
		current = next_node;
		close(STDOUT_FILENO);
	}
}

void	redir_output(t_shell *shell, t_exec *exec)
{
	close(STDOUT_FILENO);
	//exec->operator = PIPE;
	remove_output_node(shell, exec);
	/*while (exec->next->operator == GREAT
		|| exec->next->operator == APPEND)
	{
		if (exec->operator == GREAT)
		{
			//exec->operator = PIPE;
			ft_open(exec->next->token[0], O_TRUNC);
		}
		else if (exec->operator == APPEND)
		{
			//exec->operator = PIPE;
			ft_open(exec->next->token[0], O_APPEND);
		}
		exec = exec->next;
		close(STDOUT_FILENO);
	}*/
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
	free_double(first->next->token);
	free(first->next);
	if (exec->next->next)
		third = exec->next->next;
	else
		third = NULL;
	first->next = third;
	return (first);
}

void    redir_exe(t_shell *shell, t_exec *exec)
{
    t_exec  *temp;
    temp = exec;
    if (exec->operator == LESS)
        less(shell, exec);
    else if (exec->operator == HEREDOC)
        heredoc(exec);
    else
        redir_output(shell, exec);
    //print_exec(shell);
    if (temp->next && temp->operator == LESS)
    {
        temp->operator = NONE;
        temp = cat_exec(temp);
    }
	else if (!temp->next && (temp->operator == LESS))
		temp->operator = NONE;
    else if (temp->next && (temp->operator == APPEND || temp->operator == GREAT))
    {
        temp->operator = PIPE;
    }
    else if (!temp->next && (temp->operator == APPEND || temp->operator == GREAT))
    {
        temp->operator = NONE;
    }
    //if (pipe_check(temp) || input_redir_check(temp))
    {
        //temp = cat_exec(temp);
    }
    //print_exec(shell);
    //print_token(temp->token);
    /*while (exec->operator != NONE && exec->operator != PIPE)
        exec = exec->next;*/
    if (exec->operator == NONE)
        exec_cmd(shell, temp);
    else
        pipe_exe(shell, exec);
}
