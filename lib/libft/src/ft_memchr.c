/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:49:20 by kaan              #+#    #+#             */
/*   Updated: 2024/02/06 15:17:18 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		cc;
	size_t				i;

	p = s;
	cc = c;
	i = 0;
	while (i < n)
	{
		if (p[i] == cc)
		{
			return ((void *)&p[i]);
		}
		i++;
	}
	return (NULL);
}
