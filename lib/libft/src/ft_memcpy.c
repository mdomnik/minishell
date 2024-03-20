/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:51:04 by kaan              #+#    #+#             */
/*   Updated: 2024/02/06 15:17:31 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		*(d++) = *(s++);
		n--;
	}
	return (dest);
}
