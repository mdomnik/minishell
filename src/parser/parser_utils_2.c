/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:29:20 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/22 19:35:44 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void remove_nodes_till_pipe(t_shell *shell)
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

void set_index_exec(t_shell *shell)
{
	t_exec *exec;
	int		i;

	i = 0;
	exec = shell->exec;
	while(exec != NULL)
	{
		exec->index = i;
		i++;
		exec = exec->next;
	}
}