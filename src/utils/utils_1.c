/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:41:28 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/25 14:14:12 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Duplicates a double null-terminated string array.
 *
 * This function takes a double null-terminated string array
 * and creates a deep copy of it.
 * It allocates memory for the new array and duplicates each 
 * string element using ft_strdup.
 * If any memory allocation fails, it frees the previously 
 * allocated memory and returns NULL.
 *
 * @param str The double null-terminated string array to be duplicated.
 * @return A new double null-terminated string array that is a 
 * deep copy of the input array,
 *         or NULL if any memory allocation fails.
 */
char	**double_dup(char **str)
{
	int		i;
	char	**ret;

	i = 0;
	while (str[i] != NULL)
		i++;
	ret = (char **)malloc((i + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		ret[i] = ft_strdup(str[i]);
		if (ret[i] == NULL)
		{
			free_double(ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * Frees the memory allocated for a double string array.
 *
 * @param double_str The double string array to be freed.
 */
void	free_double(char **double_str)
{
	int	i;

	i = 0;
	if (double_str == NULL)
		return ;
	while (double_str[i] != NULL)
	{
		free(double_str[i]);
		i++;
	}
	free(double_str);
}

/**
 * Calculates the length of a string.
 *
 * @param s The string to calculate the length of.
 * @return The length of the string.
 */
int	ft_strlen_ms(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	update_pwd_oldpwd(t_shell *shell, char *pwd_str, char *o_pwd_str)
{
	int		i;

	i = 0;
	while (ft_strncmp("PWD=", shell->env[i], 4) != 0)
		i++;
	if (shell->env[i] != NULL)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin_ms("PWD=", ft_strdup(pwd_str));
	}
	i = 0;
	while (ft_strncmp("OLDPWD=", shell->env[i], 7) != 0)
		i++;
	if (shell->env[i] != NULL)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin_ms("OLDPWD=", ft_strdup(o_pwd_str));
	}
	update_declare_pwd(shell, ft_strdup(pwd_str), ft_strdup(o_pwd_str));
	free(pwd_str);
	free(o_pwd_str);
}

void	update_declare_pwd(t_shell *shell, char *pwd_str, char *o_pwd_str)
{
	int		i;

	i = 0;
	while (ft_strncmp("PWD=", shell->declare[i], 4) != 0)
		i++;
	if (shell->declare[i] != NULL)
	{
		free(shell->declare[i]);
		shell->declare[i] = ft_strjoin_ms("PWD=", ft_strdup(pwd_str));
	}
	i = 0;
	while (ft_strncmp("OLDPWD=", shell->declare[i], 7) != 0)
		i++;
	if (shell->declare[i] != NULL)
	{
		free(shell->declare[i]);
		shell->declare[i] = ft_strjoin_ms("OLDPWD=", ft_strdup(o_pwd_str));
	}
	free(pwd_str);
	free(o_pwd_str);
}
