/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:21:56 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/24 15:27:43 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Retrieves the value of an environment variable.
 *
 * This function searches for the specified key in the given environment array
 * and returns the corresponding value. The key is case-sensitive.
 *
 * @param key The key of the environment variable to retrieve.
 * @param env The array of environment variables.
 * @return The value of the environment variable if found, or NULL if not found.
 */
char	*ft_getenv(char *key, char **env)
{
	int		i;
	int		key_len;
	char	*value;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=')
			{
				value = ft_strdup(ft_strchr(env[i], '=') + 1);
				return (value);
			}
		}
		i++;
	}
	return (NULL);
}

/**
 * Adjusts the lexer by setting the 'join' flag for consecutive
 * non-word tokens followed by a word token.
 * This function is used in the context of a shell program.
 *
 * @param shell The shell structure containing the lexer.
 */
void	adjust_lexer_redir(t_shell *shell)
{
	t_lexer	*lexer;

	lexer = shell->lexer;
	while (lexer != NULL)
	{
		if (lexer->token != T_WORD)
		{
			if (lexer->next != NULL && lexer->next->token == T_WORD)
				lexer->next->join = 1;
		}
		lexer = lexer->next;
	}
}

/**
 * Checks the final lexer to ensure correct syntax.
 * If a redirection is followed by a pipe token, it displays an error message.
 * @param shell The shell structure.
 */
void	check_final_lexer(t_shell *shell)
{
	t_lexer	*lexer;

	lexer = shell->lexer;
	while (lexer->next != NULL)
	{
		if (find_redir(lexer->word) != 0 && lexer->next->token == T_PIPE)
			ft_perror(ERR_SYNTAX, NULL, 258, shell);
		lexer = lexer->next;
	}
	if (find_redir(lexer->word) != 0)
		ft_perror(ERR_SYNTAX, NULL, 258, shell);
}

/**
 * Finds the type of redirection based on the given string.
 *
 * @param str The string to check for redirection.
 * @return The type of redirection found.
 *         Possible values are: PIPE, GREAT, LESS, HEREDOC,
 *APPEND, T_MISTAKE, NONE.
 */
int	find_redir(char *str)
{
	if (!ft_memcmp_ms(str, "|"))
		return (PIPE);
	else if (!ft_memcmp_ms(str, ">"))
		return (GREAT);
	else if (!ft_memcmp_ms(str, "<"))
		return (LESS);
	else if (!ft_memcmp_ms(str, "<<"))
		return (HEREDOC);
	else if (!ft_memcmp_ms(str, ">>"))
		return (APPEND);
	else if (!ft_memcmp_ms(str, "<>"))
		return (T_MISTAKE);
	return (NONE);
}

/**
 * Compares two memory areas.
 *
 * This function compares the first `len` 
 * bytes of memory areas `s1` and `s2`.
 * It returns an integer less than, equal to,
 * or greater than zero if `s1` is found,
 * respectively, to be less than, to match, or be greater than `s2`.
 *
 * @param s1 The first memory area to compare.
 * @param s2 The second memory area to compare.
 * @return An integer less than, equal to, or greater than zero if `s1` is found,
 * respectively, to be less than, to match, or be greater than `s2`.
 */
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
