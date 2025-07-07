/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:31:39 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 15:32:34 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (n == 0 || dest == src)
	{
		return (dest);
	}
	if (s < d && d < s + n)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*(d--) = *(s--);
	}
	else
	{
		while (n--)
			*(d++) = *(s++);
	}
	return (dest);
}
