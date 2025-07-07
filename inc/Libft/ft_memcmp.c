/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:18:35 by opopov            #+#    #+#             */
/*   Updated: 2024/11/19 15:36:35 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				a;
	const unsigned char	*str1;
	const unsigned char	*str2;

	a = 0;
	str1 = s1;
	str2 = s2;
	while (a < n)
	{
		if (str1[a] != str2[a])
			return (str1[a] - str2[a]);
		a++;
	}
	return (0);
}
