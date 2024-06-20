/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:46:55 by kaan              #+#    #+#             */
/*   Updated: 2024/06/20 17:24:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_d_lst(char **list)
{
	size_t	i;

	i = 0;
	if (!list)
		return ;
	while (list[i])
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
}

void	invalid_identifer(char *var_name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(var_name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

// int	unset_var(char *var_name, t_envp **envp)
// {
// 	t_envp	*temp;
// 	t_envp	*next_node;

// 	temp = *envp;
// 	if (ft_strchr(var_name, '='))
// 	{
// 		invalid_identifer(var_name);
// 		return (EXIT_FAILURE);
// 	}
// 	while (temp && temp->next != NULL)
// 	{
// 		if (strcmp_msn(var_name, temp->next->var_name))
// 		{
// 			next_node = temp->next->next;
// 			free(temp->next->var_name);
// 			free(temp->next->var_value);
// 			free(temp->next);
// 			temp->next = next_node;
// 			break ;
// 		}
// 		temp = temp->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

bool	unexpected_token(char token)
{
	ft_putstr_fd("UNEXPECTED_TOKEN", STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (true);
}

bool	ft_isnum_bool(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
