/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:40:36 by kaan              #+#    #+#             */
/*   Updated: 2024/02/06 15:19:14 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	char_c;

	i = 0;
	char_c = (char)c;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == char_c)
			return ((char *) &str[i]);
		i--;
	}
	if (char_c == '\0')
		return ((char *) &str[i]);
	return (NULL);
}
