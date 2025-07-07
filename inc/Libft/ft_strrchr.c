/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:57:43 by opopov            #+#    #+#             */
/*   Updated: 2024/11/27 11:37:39 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		a++;
	}
	if (c == '\0')
	{
		return ((char *)&s[a]);
	}
	while (a >= 0)
	{
		if (s[a] == (char) c)
		{
			return ((char *)&s[a]);
		}
		a--;
	}
	return (NULL);
}
