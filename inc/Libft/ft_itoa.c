/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:09 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 18:13:46 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*itoa_calc(char *res, int m, int n, size_t a)
{
	while (n > 0)
	{
		res[a] = (n % 10) + '0';
		n /= 10;
		a--;
	}
	if (m != 0)
		res[0] = '-';
	return (res);
}

static int	itoa_minus(int *n, size_t *a, int *m)
{
	if ((*n) < 0)
	{
		if ((*n) == -2147483648)
			return (-1);
		(*n) *= -1;
		(*m)++;
		(*a)++;
	}
	if ((*n) == 0)
		return (0);
	return (1);
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	a;
	int		n1;
	int		m;

	a = 0;
	m = 0;
	if (itoa_minus(&n, &a, &m) == 0)
		return (ft_strdup("0"));
	if (itoa_minus(&n, &a, &m) == -1)
		return (ft_strdup("-2147483648"));
	n1 = n;
	while (n1 > 0)
	{
		n1 = n1 / 10;
		a++;
	}
	res = (char *)malloc((a + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[a] = '\0';
	a -= 1;
	res = itoa_calc(res, m, n, a);
	return (res);
}
