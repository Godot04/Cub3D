/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:57:27 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 18:03:13 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s1;
	size_t	a;

	a = 0;
	while (s[a] != '\0')
	{
		a++;
	}
	s1 = (char *)malloc((a + 1) * sizeof(char));
	if (s1 == NULL)
	{
		return (NULL);
	}
	a = 0;
	while (s[a] != '\0')
	{
		s1[a] = s[a];
		a++;
	}
	s1[a] = '\0';
	return (s1);
}
