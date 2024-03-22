/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:40:19 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/22 16:29:30 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_prompt *init_prompt(t_prompt *prompt)
{
	prompt = malloc(sizeof(t_prompt));
	prompt->envp = malloc(sizeof(t_envll)); 
	prompt->lexer = NULL;
	prompt->parser = malloc(sizeof(t_parser));
	prompt->printable = 0;
	return (prompt);
}

//duplicates a double pointer
char	**double_dup(char **str)
{
	int	i;
	char **ret;

	i = 0;
	while(str[i] != NULL)
		i++;
	ret = (char **)malloc((i + 1) * sizeof(char *));
	if (!ret)
		return(NULL);
	i = 0;
	while(str[i] != NULL)
	{
		ret[i] = ft_strdup(str[i]);
		if (ret[i] == NULL)
		{
			free_double(ret);
			return (ret);
		}
		i++;
	}
	return (ret);
}

//free double pointer if error occurs
void	free_double(char **double_str)
{
	int	i;

	i = 0;
	while (double_str[i])
	{
		free(double_str[i]);
		i++;
	}
	free(double_str);
}

//prints the entire stack (linked list)
void	print_lexer(t_prompt *prompt)
{
	t_lexer	*current;

	current = prompt->lexer;
	if (prompt->lexer == NULL)
	{
		printf("Stack is empty\n");
	}
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("word: [%s] ", current->word);
		printf("token: [%d] ", current->token);
		printf("index: [%d]\n", current->index);
		current = current->next;
	}
}