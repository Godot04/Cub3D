/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:30:10 by opopov            #+#    #+#             */
/*   Updated: 2024/11/20 13:24:18 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (big[0] == '\0')
		return (NULL);
	while (big[a] != '\0' && a < len)
	{
		b = 0;
		while (big[a + b] == little[b] && (a + b) < len)
		{
			if (little[b + 1] == '\0')
				return ((char *)&big[a]);
			b++;
		}
		a++;
	}
	return (NULL);
}
