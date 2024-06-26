/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:58:23 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/26 13:15:50 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Expands the environmental variables and performs tokenization.
 * 
 * @param shell The shell structure.
 */
void	expander(t_shell *shell)
{
	t_lexer	*lexer;
	char	*string;
	int		boolean;

	boolean = 0;
	string = NULL;
	lexer = shell->lexer;
	if (lexer->next == NULL && lexer->token == T_PIPE)
		ft_perror(ERR_SYNTAX, NULL, 258, shell);
	env_expander(lexer, 0, shell);
	process_lexer(shell, lexer, string, boolean);
	lexerfreelist_ms(&shell->lexer);
	remove_empty_expand(shell);
	if (shell->expand != NULL)
		parser(shell);
}

/**
 * Expands environment variables in the given shell command.
 *
 * @param shell The shell structure containing environment variables.
 * @param lexer The lexer structure containing the command tokens.
 * @param i The index variable used for iteration.
 */
void	env_expander(t_lexer *lexer, int i, t_shell *shell)
{
	char	*temp;
	char	**env_split;

	while (lexer != NULL)
	{
		i = 0;
		if (lexer->token == T_WORD && lexer->quote == 0)
		{
			env_split = add_delim_split(lexer->word, shell);
			while (env_split[i] != NULL)
			{
				env_split[i] = search_replace_env(env_split[i], shell, 0, 1);
				i++;
			}
			i = 0;
			temp = NULL;
			while (env_split[i] != NULL)
				temp = ft_strjoin(temp, env_split[i++]);
			free(lexer->word);
			lexer->word = ft_strdup(temp);
			free_double(env_split);
			free(temp);
		}
		lexer = lexer->next;
	}
}

/**
 * @brief Searches and replaces environment variables in a given string.
 * 
 * This function searches for environment variables in the input string
 * and replaces them with their corresponding values.
 * If an environment variable is not found, it is replaced with an empty string.
 * 
 * @param str The input string to search and replace environment variables in.
 * @param shell A pointer to the shell structure.
 * @return The modified string with environment variables replaced.
 */
char	*search_replace_env(char *str, t_shell *shell, int i, int j)
{
	char	*temp;
	char	*ret;

	while (str[i] != '$' && str[i] != '\0') 
		i++;
	if (str[i] == '\0') 
		return (str);
	while (str[i + j] != '$' && str[i + j] != '\0'
		&& str[i + j] != ' ' && str[i + j] != 39)
		j++;
	if (j == 1)
		return (str);
	temp = ft_substr(str, (i + 1), j - 1);
	ret = give_ret_search_replace(shell, temp);
	temp = ft_substr(str, (i + j), (ft_strlen(str) - (i + j)));
	ret = ft_strjoin(ret, temp);
	free(str);
	str = ft_strdup(ret);
	if (ret)
		free(ret);
	free(temp);
	return (str);
}

char	*give_ret_search_replace(t_shell *shell, char *temp)
{
	char	*ret;
	char	*tempy;

	if (temp[0] == '?')
	{
		ret = ft_itoa(*shell->exit_status);
		tempy = ft_substr(temp, 1, ft_strlen(temp) - 1);
		ret = ft_strjoin(ret, tempy);
		free(tempy);
	}
	else
		ret = ft_getenv(temp, shell->env);
	if (!ret)
		ret = ft_strdup("");
	free(temp);
	return (ret);
}
