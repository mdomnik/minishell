/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:34:13 by kaan              #+#    #+#             */
/*   Updated: 2024/02/06 15:18:37 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	if (d_len >= size)
	{
		d_len = size;
	}
	if (d_len == size)
	{
		return (size + s_len);
	}
	if (s_len < size - d_len)
		ft_memcpy(dest + d_len, src, s_len +1);
	else
	{
		ft_memcpy(dest + d_len, src, size - d_len - 1);
		dest[size - 1] = '\0';
	}
	return (d_len + s_len);
}
