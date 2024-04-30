/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:48:09 by kaan              #+#    #+#             */
/*   Updated: 2024/04/30 15:03:29 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ps;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ps = ft_calloc(len + 1, sizeof(char));
	if (!ps)
		return (NULL);
	while (i < len)
	{
		ps[i] = s[start + i];
		i++;
	}
	return (ps);
}
