/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:56:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 14:58:51 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// adjusts the operators giving the previous node the next node's operator
void	adjust_exec_operand(t_shell *shell, int pipe_count)
{
	t_exec	*exec;
	int		temp_operand;

	exec = shell->exec;
	temp_operand = NONE;
	while (pipe_count > 0 && exec->next != NULL)
	{
		if (exec->operator == PIPE)
			pipe_count--;
		exec = exec->next;
	}
	while (exec->next != NULL)
	{
		temp_operand = exec->operator;
		exec->operator = exec->next->operator;
		exec->next->operator = temp_operand;
		exec = exec->next;
	}
	if (shell->expand != NULL)
		exec->operator = PIPE;
	else
		exec->operator = NONE;
}

//	gives the token count to the exec struct, which displays the number
// 	of arguments in a token array
void	set_token_count(t_shell *shell)
{
	t_exec	*exec;
	int		count;

	exec = shell->exec;
	count = 0;
	while (exec != NULL)
	{
		if (exec->token != NULL)
		{
			count = 0;
			while (exec->token[count] != NULL)
				count++;
			exec->token_count = count;
		}
		exec = exec->next;
	}
}

/**
 * Creates a redirection node and adds it to the execution list in the shell.
 *
 * @param shell The shell structure.
 * @param file The file to be redirected.
 * @param type The type of redirection (e.g., input, output, append).
 */
void	create_redir_node(t_shell *shell, char *file, int type)
{
	t_exec	*node;
	char	**token;

	node = (t_exec *)malloc(sizeof(t_exec));
	token = (char **)malloc(2 * sizeof(char *));
	token[0] = ft_strdup(file);
	token[1] = NULL;
	node->operator = type;
	node->token = token;
	node->token_count = 0;
	node->next = NULL;
	execaddback_ms(&shell->exec, node);
}

//removes all nodes until the pipe operator or end of expand list
void	remove_nodes_till_pipe(t_shell *shell)
{
	t_expand	*temp;

	while (shell->expand != NULL && shell->expand->token != T_PIPE)
	{
		temp = shell->expand->next;
		free(shell->expand->word);
		free(shell->expand);
		shell->expand = temp;
	}
	if (shell->expand != NULL)
	{
		temp = shell->expand->next;
		free(shell->expand->word);
		free(shell->expand);
		shell->expand = temp;
	}
	if (shell->expand != NULL)
		shell->expand->prev = NULL;
}

//gives an index value to the exec struct nodes
void	set_index_exec(t_shell *shell)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = shell->exec;
	while (exec != NULL)
	{
		exec->index = i;
		i++;
		exec = exec->next;
	}
}
