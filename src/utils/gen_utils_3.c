/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:50:00 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/30 21:29:50 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Adds quotes around the value of a string variable.
 *
 * @param str The string variable to add quotes to.
 * @param var A flag indicating whether to free the original string variable.
 * @return The modified string with quotes added around the value.
 */
char	*add_value_quotes(char *str, int var)
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

/**
 * Sorts the elements in the `declare` 
 * array of the `shell` structure in ascending order.
 * 
 * @param shell The shell structure containing the `declare` array to be sorted.
 */
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
			if (ft_strncmp(shell->declare[i],
					shell->declare[j], ft_strlen(shell->declare[i])) > 0)
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

/**
 * Scans the environment variables in the shell
 * and updates the value of a specific variable.
 *
 * @param shell The shell structure containing the environment variables.
 * @param str The string representing the variable to be updated.
 * @return 1 if the variable was found and updated successfully, 0 otherwise.
 */
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

/**
 * Scans and declares a variable in the shell.
 *
 * This function scans a string and extracts the variable name and value.
 * It then adds the variable to the shell's environment.
 *
 * @param shell The shell structure.
 * @param str The string to scan and declare.
 * @return 1 if the variable was successfully declared, 0 otherwise.
 */
int	scan_declare(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * 2);
	while (str[i] != '=' && str[i])
		i++;
	tmp[1] = ft_substr(str, 0, i);
	if (str[i] != '\0')
		tmp[0] = add_value_quotes(str, 0);
	j = i;
	if (scan_declare_2(shell, tmp, str, j) == 1)
		return (1);
	free(tmp[1]);
	if (str[j] != '\0')
		free(tmp[0]);
	free(tmp);
	return (0);
}

/**
 * Scans and updates the declaration array in the shell structure.
 * 
 * @param shell The shell structure.
 * @param tmp The temporary array containing the variable and value.
 * @param str The string to be scanned for the presence of '='.
 * @param j The index of the character in the string.
 * @return 1 if the declaration is found and updated, 0 otherwise.
 */
int	scan_declare_2(t_shell *shell, char **tmp, char *str, int j)
{
	int	i;

	i = 0;
	while (shell->declare[i])
	{
		if (ft_strncmp(tmp[1], shell->declare[i], ft_strlen(tmp[1])) == 0)
		{
			if (ft_strchr(str, '=') != NULL && tmp[0])
			{
				free(shell->declare[i]);
				shell->declare[i] = ft_strdup(tmp[0]);
			}
			free(tmp[1]);
			if (str[j] != '\0')
				free(tmp[0]);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}
