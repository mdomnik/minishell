/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:50:00 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/30 15:54:34 by mdomnik          ###   ########.fr       */
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
		shell->declare[i] = add_value_quotes(shell->declare[i], 1);
		if (!shell->declare[i])
			free_err(ERR_MALLOC, shell);
		i++;
	}
}

char *add_value_quotes(char *str, int var)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = NULL;
	tmp = NULL;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '\0')
		return (str);
	tmp = ft_substr(str, i + 1, ft_strlen(str) - i);
	ret = ft_substr(str, 0, i);
	ret = ft_strjoin(ret, "=\"");
	ret = ft_strjoin(ret, tmp);
	ret = ft_strjoin(ret, "\"");
	if (var == 1)
		free(str);
	free(tmp);
	return (ret);
	
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

int	scan_env(t_shell *shell, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '=' && str[i])	
		i++;
	tmp = ft_substr(str, 0, i);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(tmp, shell->env[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			free(shell->env[i]);
			shell->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	scan_declare(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (str[i] != '=' && str[i])	
		i++;
	tmp2 = ft_substr(str, 0, i); //whats before the equal sign
	if (str[i] != '\0')
		tmp = add_value_quotes(str, 0); //add quotes to the value key="value"
	j = i;
	i = 0;
	while (shell->declare[i])
	{
		if (ft_strncmp(tmp2, shell->declare[i], ft_strlen(tmp2)) == 0)
		{
			if (ft_strchr(str, '=') != NULL && tmp)
			{
				free(shell->declare[i]);
				shell->declare[i] = ft_strdup(tmp);
			}
			if (str[j] != '\0')
				free(tmp);
			free(tmp2);
			return (1);
		}
		i++;
	}
	free(tmp2);
	if (str[j] != '\0')
		free(tmp);
	return (0);
}
