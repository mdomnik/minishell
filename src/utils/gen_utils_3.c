/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:50:00 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/30 00:24:33 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	prep_declare(t_shell *shell)
{
	int		i;

	i = 0;
	sort_declare(shell);
	while (shell->declare[i])
	{
		shell->declare[i] = add_value_quotes(shell->declare[i]);
		if (!shell->declare[i])
			free_err(ERR_MALLOC, shell);
		i++;
	}
}

char *add_value_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen_ms(str) + 3));
	if (!new_str)
		return (NULL);
	while (str[i] != '=' && str[i] != '\0')
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	if (str[i] == '\0')
	{
		free(new_str);
		return (str);
	}
	new_str[j] = str[i];
	j++;
	new_str[j] = '"';
	j++;
	i++;
	while (str[i] != '\0')
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '"';
	j++;
	new_str[j] = '\0';
	return (new_str);
}

void	sort_declare(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (shell->declare[i])
	{
		j = i + 1;
		while (shell->declare[j])
		{
			if (ft_strncmp(shell->declare[i], shell->declare[j], ft_strlen(shell->declare[i])) > 0)
			{
				tmp = shell->declare[i];
				shell->declare[i] = shell->declare[j];
				shell->declare[j] = tmp;
			}
			j++;
		}
		i++;
	}
}