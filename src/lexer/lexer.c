/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:24:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 20:27:52 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//splits prompt into tokens and nodes of the lexer linked list
void split_tokens(t_prompt *prompt)
{
	int		i;

	i = 0;
	prompt->line = trim_whitespace(prompt->line);
	while(prompt->line[i] != '\0')
	{
		if(!is_whitespace_null(prompt->line[i]))
		{
			prompt->word = ft_strdup("");
			if (prompt->word == NULL)
				simple_err(ERR_MALLOC);
			i = node_process(prompt, i);
		}
		else
				i++;
	}
	reset_increment_i(0);
	restructure_prompt(prompt);
}

int	node_process(t_prompt *prompt, int	i)
{
	int		q;
	char	*temp;
	t_tokens	token;

	while (!is_whitespace_null(prompt->line[i]))
	{
		temp = ft_strdup("");
		token = T_WORD;
		q = 0;
		if (is_quote(prompt->line[i]))
		{
			q = is_quote(prompt->line[i++]);
			while(prompt->line[i] != q && prompt->line[i] != '\0')
				temp = append_char_env(temp, prompt->line[i++]);
			if(prompt->line[i] == '\0')
				simple_err(ERR_QUOTE);
			i++;
		}
		else 
			while(!is_quote(prompt->line[i]) && !is_whitespace_null(prompt->line[i]))
				temp = append_char_env(temp, prompt->line[i++]);
		if (q == 0)
		{
			temp = search_redir(prompt, temp);
			if (prompt->printable == 1)
			{
				free(prompt->word);
				prompt->word = NULL;
				prompt->printable = 0;
			}
		}
		if (q != 39)
			temp = search_replace_env(prompt, temp);
		prompt->word = ft_strjoin(prompt->word, temp);
		free(temp);
	}
	if (prompt->word[0] != '\0')
		add_node(prompt, prompt->word, T_WORD);
	return(i);
}

char	*search_replace_env(t_prompt *prompt, char *str)
{
	int		i;
	int		j;
	char	*env_name;
	char	*env_value;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '$')
	{
		env_name = (char *)malloc(((ft_strlen(str) - i) + 1) * sizeof(char));
		i++;
		while (str[i + j] != '\0')
		{
			env_name[j] = str[i + j]; 
			j++;
		}
		env_name[j] = '\0';
		env_value = getenv(env_name);
		free(env_name);
		if (env_value == NULL)
		{
			new = removed_env(str);
			str = ft_strdup(new);
			free(new);
		}
		else
		{
			env_value = ft_strdup(env_value);
			str = updated_env_str(str, env_value);
			str = makes_nodes_env(prompt, str);
			free(prompt->word);
			prompt->word = NULL;
			free(env_value);
		}
	}
	return(str);
}

char	*replace_env(char	*env_name, char	*env_str)
{
	int		i;
	int		j;
	char	*replace;


	i = 0;
	j = 0;
	while (!ft_strncmp(env_name, env_str, i))
		i++;
	replace = (char *)malloc(((ft_strlen(env_str) - i) + 1) * sizeof(char));
	while (env_str[i + j] != '\0')
	{
		replace[j] = env_str[i + j];
		j++;
	}
	free(env_name);
	return(replace);
}

char 	*updated_env_str(char *str, char *env_str)
{
	int		i;
	char	*cat;

	i = 0;
	while(str[i] != '$' && str[i] != '\0')
		i++;
	cat = (char *)malloc((i + ft_strlen(env_str) + 1) * sizeof(char));
	i = 0;
	while(str[i] != '$' && str[i] != '\0')
	{
		cat[i] = str[i];
		i++;
	}
	cat[i] = '\0';
	str = ft_strjoin(cat, env_str);
	return (str);
}