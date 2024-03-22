/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:58:47 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 16:37:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

int	ft_strlen_ms(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void add_node(t_prompt *prompt, char *word, t_tokens token)
{
	t_lexer *new;
	
	new = lexernew_ms(word, token);
	lexeraddback_ms(&prompt->lexer, new);
}