/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:39:35 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/24 15:22:14 by mdomnik          ###   ########.fr       */
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