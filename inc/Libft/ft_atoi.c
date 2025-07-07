/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:23:07 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 18:01:26 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_spacecalc(const char *nptr, int a)
{
	while (nptr[a] == ' ' || nptr[a] == '\n'
		|| nptr[a] == '\t' || nptr[a] == '\v'
		|| nptr[a] == '\f' || nptr[a] == '\r')
	{
		a++;
	}
	return (a);
}

static int	ft_plusminus(const char *nptr, int *a, int min)
{
	if (nptr[*a] == '-' || nptr[*a] == '+')
	{
		if (nptr[*a] == '-')
		{
			min *= -1;
		}
		(*a)++;
	}
	return (min);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	a;
	int	min;

	res = 0;
	a = 0;
	min = 1;
	a = ft_spacecalc(nptr, a);
	min = ft_plusminus(nptr, &a, min);
	while (nptr[a] >= '0' && nptr[a] <= '9')
	{
		if (min == 1 && res > (2147483647 - (nptr[a] - '0')) / 10)
			return (-1);
		if (min == -1 && res > (2147483648 - (nptr[a] - '0')) / 10)
			return (0);
		res = res * 10 + (nptr[a] - '0');
		a++;
	}
	return (res * min);
}
