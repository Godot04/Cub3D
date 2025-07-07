/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:08:13 by opopov            #+#    #+#             */
/*   Updated: 2024/11/20 13:16:46 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	if (n == 0)
	{
		return (0);
	}
	a = 0;
	while (s1[a] && s2[a] && a < n)
	{
		if (s1[a] != s2[a])
		{
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		}
		a++;
	}
	if (a < n)
	{
		return ((unsigned char)s1[a] - (unsigned char)s2[a]);
	}
	return (0);
}
