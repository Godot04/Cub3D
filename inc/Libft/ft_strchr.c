/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:26:02 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 17:10:18 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char ) c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((unsigned char ) c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}
