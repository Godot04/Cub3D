/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:04:07 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 18:17:15 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	b;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
	{
		return (src_len + size);
	}
	b = 0;
	while (b < (size - dst_len - 1) && src[b])
	{
		dst[dst_len + b] = src[b];
		b++;
	}
	if (dst_len + b < size)
	{
		dst[dst_len + b] = '\0';
	}
	return (src_len + dst_len);
}
