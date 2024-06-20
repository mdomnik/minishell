/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:26:32 by kaan              #+#    #+#             */
/*   Updated: 2024/06/20 15:41:32 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_envp	*envp_new_node(char *var_name, char *var_value, bool is_exported)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	new_node->var_name = var_name;
	new_node->var_value = var_value;
	new_node->is_exported = is_exported;
	new_node->next = NULL;
	return (new_node);
}

t_envp	*envp_last(t_envp *node)
{
	while (node)
	{
		if (!node->next)
			break ;
		node = node->next;
	}
	return (node);
}

void	envp_add_back(t_envp **envp, t_envp *new)
{
	t_envp	*temp;

	if (envp)
	{
		if (!*envp)
			*envp = new;
		else
		{
			temp = envp_last(*(envp));
			temp->next = new;
		}
	}
}

char	*get_varvalue_envp(char *var_name, t_shell *shell)
{
	char	*var_value;

	var_value = get_envp(var_name, &shell->envp_lst);
	free(var_name);
	return (var_value);
}

char	*get_envp(char *var_name, t_envp **envp)
{
	t_envp	*temp;

	temp = *envp;
	while (temp != NULL)
	{
		if (strcmp_msn(var_name, temp->var_name))
			return (temp->var_value);
		temp = temp->next;
	}
	return (NULL);
}
