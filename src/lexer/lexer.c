/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:24:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/20 22:35:11 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//splits prompt into tokens and nodes of the lexer linked list
void split_tokens(t_prompt *prompt)
{
	int		i;
	char	*word;

	i = 0;
	prompt->line = trim_whitespace(prompt->line);
	while(prompt->line[i] != '\0')
	{
		if(!is_whitespace_null(prompt->line[i]))
		{
			word = NULL;
			i = node_process(prompt, i, word);
		}
		if(prompt->line[i] != '\0')
				i++;
	}
	// print_lexer(prompt);
	lexerfreelist_ms(&prompt->lexer);
}

int	node_process(t_prompt *prompt, int	i, char *word)
{
	int		q;
	char	*temp;
	t_lexer *new;

	(void)new;
	while (!is_whitespace_null(prompt->line[i]))
	{
		temp = NULL;
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
		if (q != 39)
			temp = search_replace_env(prompt, temp);
		word = ft_strjoin(word, temp);
	}
	printf("word: %s\n", word);
	// check_env_make_node(prompt, word);
	return(i);
}

char	*search_replace_env(t_prompt *prompt, char *str)
{
	char	**env;
	char	*env_name;
	int		i;
	int		j;

	env = prompt->envp->env;
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
		j = 0;
		while (env[j] != NULL)
		{
			if (!ft_strncmp(env_name, env[j], ft_strlen(env_name)))
				break ;
			j++;
		}
		if (env[j] == NULL)
		{
			printf("no match\n");
			return (removed_env(str));
		}
		else if (!ft_strncmp(env_name, env[j], ft_strlen(env_name)))
		{
			env_name = ft_strdup(replace_env(env_name, env[j]));
			str = updated_env_str(str, env_name);
		}
		printf("test: %s\n", env_name);
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

char 	*updated_env_str(char *str, char	*env_str)
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
	str = ft_strjoin(cat, env_str);
	return (str);
}