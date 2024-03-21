/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:10:15 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/21 18:40:02 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//gets rid of all the whitespace before and after the string
char *trim_whitespace(char *str)
{
    char *temp;
    int	 i;
    int	 j;
    int	 k;

    j = (ft_strlen(str) - 1);
    i = 0;
    k = 0;
    while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    while(str[j] == 32 || (str[j] >= 9 && str[j] <= 13))
        j--;
    if (i > j) 
	{
        temp = malloc(1);
        if (!temp)
            simple_err(ERR_MALLOC);
        temp[0] = '\0';
    } 
	else 
	{
        temp = malloc((j - i + 1) + 1);
		if (!temp)
            simple_err(ERR_MALLOC);
        while((i + k) <= j)
        {
            temp[k] = str[i + k];
            k++;
        }
        temp[k] = '\0';
    }
    return(temp);
}

//checks whether a character is a whitespace (space, tabs, carrage ret)
int is_whitespace_null(char c)
{
	if (c == 32 || (c >= 9 && c <= 13) || c == '\0')
		return(1);
	return(0);
}

//checks if a char is a quote
int is_quote(char c)
{
	if (c == 34)
		return(34);
	else if (c == 39)
		return(39);
	else
		return(0);
}

char	*append_char_env(char *str, char c)
{
	int		i;
	char	*ret;

	if(str == NULL)
	{
		str = (char *)malloc(1 * sizeof(char));
		*str = '\0';
	}
	i = 0;
	while(str[i] != '\0')
	{
		i++;
	}
	ret = (char *)malloc((i + 2) * sizeof(char));
	i = 0;
	while(str[i] != '\0')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	free(str);
	return(ret);
}

char	*removed_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while(str[i] != '$')
	{
		if(str[i] == '\0')
			return(str);
		i++;
	}
	ret = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] != '$')
	{
		if(str[i] == '\0')
			return(str);
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	free(str);
	return(ret);
}
