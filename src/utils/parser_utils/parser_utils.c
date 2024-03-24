/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:39:35 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/24 18:22:30 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

void parser_check_out(t_prompt *prompt)
{
	t_parser *temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = prompt->parser;
	while (temp->next != NULL)
	{
		i++;
		temp = temp->next;
	}
	while (temp->next != NULL)
	{
		if (temp->output == 0 && j < i)
			temp->output = O_PIPE;
		else if (temp->output == 0 && j == i)
			temp->output = O_STDOUT;
		j++;
		temp = temp->next;
	}
}