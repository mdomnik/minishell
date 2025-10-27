/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:41:28 by mdomnik           #+#    #+#             */
/*   Updated: 2025/10/27 19:09:20 by mdomnik          ###   ########.fr       */
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

#include "../../inc/minishell.h"

/**
 * Safely updates PWD and OLDPWD in both shell->env and shell->declare.
 * Creates them if they don't exist.
 */
void	update_pwd_oldpwd(t_shell *shell, char *pwd_str, char *o_pwd_str)
{
	int		i;
	int		found_pwd = 0;
	int		found_oldpwd = 0;
	char	*tmp;

	if (!shell || !shell->env)
		return;

	/* ---------- Update or add to env ---------- */
	for (i = 0; shell->env[i]; i++)
	{
		if (!found_pwd && ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin_ms("PWD=", ft_strdup(pwd_str));
			found_pwd = 1;
		}
		else if (!found_oldpwd && ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin_ms("OLDPWD=", ft_strdup(o_pwd_str));
			found_oldpwd = 1;
		}
	}

	if (!found_pwd)
	{
		tmp = ft_strjoin_ms("PWD=", ft_strdup(pwd_str));
		add_env(shell, tmp);
		free(tmp);
	}
	if (!found_oldpwd)
	{
		tmp = ft_strjoin_ms("OLDPWD=", ft_strdup(o_pwd_str));
		add_env(shell, tmp);
		free(tmp);
	}

	/* ---------- Also update declare ---------- */
	update_declare_pwd(shell, pwd_str, o_pwd_str);
	/* update_declare_pwd frees pwd_str/o_pwd_str */
}

/**
 * Updates PWD and OLDPWD in shell->declare.
 * Adds them if they don't exist.
 */
void	update_declare_pwd(t_shell *shell, char *pwd_str, char *o_pwd_str)
{
	int		i;
	int		found_pwd = 0;
	int		found_oldpwd = 0;
	char	*tmp;

	if (!shell || !shell->declare)
	{
		free(pwd_str);
		free(o_pwd_str);
		return;
	}

	for (i = 0; shell->declare[i]; i++)
	{
		if (!found_pwd && ft_strncmp(shell->declare[i], "PWD=", 4) == 0)
		{
			free(shell->declare[i]);
			shell->declare[i] = ft_strjoin_ms("PWD=", ft_strdup(pwd_str));
			found_pwd = 1;
		}
		else if (!found_oldpwd && ft_strncmp(shell->declare[i], "OLDPWD=", 7) == 0)
		{
			free(shell->declare[i]);
			shell->declare[i] = ft_strjoin_ms("OLDPWD=", ft_strdup(o_pwd_str));
			found_oldpwd = 1;
		}
	}

	if (!found_pwd)
	{
		tmp = ft_strjoin_ms("PWD=", ft_strdup(pwd_str));
		append_declare(shell, tmp);
		free(tmp);
	}
	if (!found_oldpwd)
	{
		tmp = ft_strjoin_ms("OLDPWD=", ft_strdup(o_pwd_str));
		append_declare(shell, tmp);
		free(tmp);
	}

	free(pwd_str);
	free(o_pwd_str);
}

/**
 * Appends a new entry to shell->declare.
 * Works like add_env() but for the declare array.
 */
void	append_declare(t_shell *shell, char *str)
{
	char	**copy;
	int		i;

	if (!shell)
		return;

	i = 0;
	while (shell->declare && shell->declare[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 2));
	if (!copy)
		return;

	i = 0;
	while (shell->declare && shell->declare[i])
	{
		copy[i] = ft_strdup(shell->declare[i]);
		i++;
	}
	copy[i] = ft_strdup(str);
	copy[i + 1] = NULL;

	free_double(shell->declare);
	shell->declare = copy;
}
