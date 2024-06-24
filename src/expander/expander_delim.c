/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_delim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:30:59 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 20:25:30 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Splits a string by a delimiter and adds the 
 * delimiter to each split element except the first one.
 * first element is checked for '$' and if it is present,
 *  it is added to the first element.
 * @param str The string to be split.
 * @return An array of strings where each element is a split
 *  part of the original string.
 */
char	**add_delim_split(char *str, t_shell *shell)
{
	int		i;
	int		is_env;
	char	**ret;

	i = 0;
	if (str[0] == '$')
		is_env = 1;
	else
		is_env = 0;
	if (str[0] == '$' && str[1] == '$')
		return (double_dollar (str, 0));
	if (str[0] == '$' && str[1] == '\0')
		return (single_dollar());
	ret = ft_split_ms(str, '$');
	if (ret[0] == NULL)
		free_err_delim(shell, ret);
	while (ret[i] != NULL)
	{
		if (i > 0)
			ret[i] = ft_strjoin_ms("$", ret[i]);
		i++;
	}
	if (is_env == 1)
		ret[0] = ft_strjoin_ms("$", ret[0]);
	return (ret);
}

/**
 * Expands a string containing double dollar signs ($$) by replacing them
 * with the process ID.
 * 
 * @param str The input string to be expanded.
 * @return An array of strings where the first element is
 * the expanded string and the second element is NULL.
 *         Returns NULL if memory allocation fails.
 */
char	**double_dollar(char *str, int i)
{
	char	**ret;
	char	*temp;
	char	*pid;

	pid = ft_itoa(getpid());
	ret = (char **)malloc(2 * sizeof(char *));
	if (!ret)
		return (NULL);
	while (str[i] == '$')
		i++;
	temp = ft_substr(str, i, ft_strlen(str) - i);
	ret[0] = NULL;
	i = i / 2;
	while (i > 0)
	{
		ret[0] = ft_strjoin(ret[0], pid);
		i--;
	}
	if (!ret[0])
		ret[0] = ft_strjoin_ms(pid, temp);
	else
		ret[0] = ft_strjoin(ret[0], temp);
	ret[1] = NULL;
	return (ret);
}

char	**single_dollar(void)
{
	char	**ret;

	ret = (char **)malloc(2 * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup("$");
	ret[1] = NULL;
	return (ret);
}

void	free_err_delim(t_shell *shell, char **ret)
{
	free_double(ret);
	ft_perror(ERR_CMD, NULL, 258, shell);
}
