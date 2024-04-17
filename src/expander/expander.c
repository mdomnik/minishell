/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:58:23 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/17 20:34:00 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Expands the shell variables and performs tokenization.
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
	env_expander(shell, lexer, 0);
	process_lexer(shell, lexer, string, boolean);
	lexerfreelist_ms(&shell->lexer);
	parser(shell);
}

/**
 * Expands environment variables in the given shell command.
 *
 * @param shell The shell structure containing environment variables.
 * @param lexer The lexer structure containing the command tokens.
 * @param i The index variable used for iteration.
 */
void	env_expander(t_shell *shell, t_lexer *lexer, int i)
{
	char	*temp;
	char	**env_split;

	while (lexer != NULL)
	{
		i = 0;
		if (lexer->token == T_WORD && lexer->quote == 0)
		{
			env_split = add_delim_split(lexer->word);
			while (env_split[i] != NULL)
			{
				env_split[i] = search_replace_env(env_split[i], shell);
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
char	*search_replace_env(char *str, t_shell *shell)
{
	int		i;
	char	*temp;
	char	*ret;

	i = 0;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (str);
	temp = ft_substr(str, (i + 1), ft_strlen(str));
	if (!temp)
		free_err(ERR_MALLOC, shell);
	ret = getenv(temp);
	if (!ret)
		ret = ft_strdup("");
	if (!ret)
		free_err(ERR_MALLOC, shell);
	free(str);
	str = ft_substr(ret, 0, ft_strlen(ret));
	if (ret[0] == '\0')
		free(ret);
	free(temp);
	return (str);
}