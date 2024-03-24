/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:07:09 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/24 14:42:43 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char *search_redir(t_prompt *prompt, char *str)
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
		if (prompt->printable == 0 && prompt->word[0] != '\0')
		{
			add_node(prompt, prompt->word, T_WORD);
			prompt->printable = 1;
		}
		token = check_redir(str[i], str[i + 1]);
		temp = ft_substr(str, 0, i);
		if (temp[0] != '\0')
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
		str = search_redir(prompt, str);
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

char *makes_nodes_env(t_prompt *prompt, char *str)
{
	char	*semi;
	char	*node;
	int		q;
	int		i;

	i = 0;
	while(str[i] != '\0')
	{
		node = ft_strdup("");
		while (!is_whitespace_null(str[i]))
		{
			semi = NULL;
			semi = ft_strdup("");
			q = 0;
			if (is_quote(str[i]))
			{
				q = is_quote(str[i++]);
				while(str[i] != q && str[i] != '\0')
					semi = append_char_env(semi, str[i++]);
				if(str[i] == '\0')
					simple_err(ERR_QUOTE);
				i++;
			}
			else 
				while(!is_quote(str[i]) && !is_whitespace_null(str[i]))
					semi = append_char_env(semi, str[i++]);
			node = ft_strjoin(node, semi);
			if (!is_whitespace_null(semi[0]))
				break;
			i++;
		}
		if(str[i] == '\0')
			break;
		add_node(prompt, node, T_WORD);
		free(node);
		i++;
	}
	return (node);
}