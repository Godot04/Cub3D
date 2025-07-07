/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:06:17 by opopov            #+#    #+#             */
/*   Updated: 2024/11/20 14:00:25 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	size_t			a;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (!dest_str && !src_str)
	{
		return (NULL);
	}
	a = 0;
	ptr1 = (unsigned char *) src_str;
	ptr2 = (unsigned char *) dest_str;
	while (a < n)
	{
		ptr2[a] = ptr1[a];
		a++;
	}
	return (dest_str);
}
