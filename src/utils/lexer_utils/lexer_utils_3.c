/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:07:09 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 16:37:43 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char *search_redir(t_prompt *prompt, char *str, char *word)
{
	t_tokens	token;
	char		*temp;
	int			i;

	i = 0;
	while(!check_redir(str[i], str[i + 1]) && str[i + 1] != '\0')
		i++;
	if (str[i + 1] == '\0' && !check_redir(str[i], str[i + 1]))
		return (str);
	else
	{
		if (prompt->printable == 0 && word[0] != '\0')
		{
			add_node(prompt, word, T_WORD);
			prompt->printable = 1;
		}
		token = check_redir(str[i], str[i + 1]);
		temp = ft_substr(str, 0, i);
		add_node(prompt, temp, T_WORD);
		if (token == T_APPEND || token == T_HEREDOC || token == T_MISTAKE)
		{
			add_node(prompt, ft_substr(str, i, 2), token);
			str = ft_substr(str, i + 2, ft_strlen(str) - i - 2);
		}
		else
		{
			add_node(prompt, ft_substr(str, i, 1), token);
			str = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
		}
	}
	if(str[0] == '\0')
		return (str);
	else
		str = search_redir(prompt, str, word);
	return (str);
}

int	check_redir(char c1, char c2)
{
	if (!cmpchar(c1, '>') && !cmpchar(c2, '>') && c2 != '\0')
		return(T_APPEND);
	else if (!cmpchar(c1, '<') && !cmpchar(c2, '<')&& c2 != '\0')
		return(T_HEREDOC);
	else if (!cmpchar(c1, '<') && !cmpchar(c2, '>')&& c2 != '\0')
		return(T_MISTAKE);
	else if (!cmpchar(c1, '>'))
		return(T_GREATER);
	else if (!cmpchar(c1, '<'))
		return(T_LESSER);
	else if (!cmpchar(c1, '|'))
		return(T_PIPE);
	return (T_WORD);
}

int	cmpchar(char c1, char c2)
{
	if (c1 != c2)
		return (c1 - c2);
	return (0);
}