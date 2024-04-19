/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:53:27 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/19 15:09:30 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char **pop_io(char **io, char *str1, char *str2 , int token)
{
	if (token == T_LESSER || token == T_HEREDOC)
	{
		if (io[0])
			free(io[0]);
		if (io[1])
			free(io[1]);
		io[0] = ft_strdup(str1);
		io[1] = ft_strdup(str2);
	}
	else if (token == T_GREATER || token == T_APPEND)
	{
		if (io[2])
			free(io[2]);
		if (io[3])
			free(io[3]);
		io[2] = ft_strdup(str1);
		io[3] = ft_strdup(str2);
	}
	return (io);
}

char **remove_first(char **args)
{
	char **temp;
	int i;

	i = 0;
	while (args[i] != NULL)
		i++;
	temp = (char **)malloc((i) * sizeof(char *));
	i = 1;
	while(args[i] != NULL)
	{
		temp[i - 1] = ft_strdup(args[i]);
		i++;
	}
	temp[i - 1] = NULL;
	return (temp);
}

int	find_redir(char *str)
{
	if (!ft_memcmp_ms(str, "|"))
		return(T_PIPE);
	else if (!ft_memcmp_ms(str, ">"))
		return(T_GREATER);
	else if (!ft_memcmp_ms(str, "<"))
		return(T_LESSER);
	else if (!ft_memcmp_ms(str, "<<"))
		return(T_HEREDOC);
	else if (!ft_memcmp_ms(str, ">>"))
		return(T_APPEND);
	else if (!ft_memcmp_ms(str, "<>"))
		return(T_MISTAKE);
	return (T_WORD);
}

int	ft_memcmp_ms(const void *s1, const void *s2)
{
	char	*p1;
	char	*p2;
	int		i;
	int		len;

	p1 = (char *)s1;
	p2 = (char *)s2;
	len = ft_strlen_ms(p1);
	i = 0;
	if (len != ft_strlen_ms(p2))
		return (-1);
	while (i < len)
	{
		if (p1[i] != p2[i])
		{
			return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}
