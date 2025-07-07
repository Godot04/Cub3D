/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:51:19 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 18:14:16 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fd_funct(int *n, int *fd)
{
	if ((*n) < 0)
	{
		if ((*n) == -2147483648)
		{
			write((*fd), "-2147483648", 11);
			return (-1);
		}
		(*n) *= -1;
		write((*fd), "-", 1);
	}
	if ((*n) == 0)
	{
		write((*fd), "0", 1);
		return (0);
	}
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		a;
	char	s[12];

	a = 0;
	if (fd_funct(&n, &fd) <= 0)
		return ;
	while (n > 0)
	{
		s[a] = (n % 10) + '0';
		n /= 10;
		a++;
	}
	s[a] = '\0';
	while (a > 0)
	{
		a--;
		write(fd, &s[a], 1);
	}
}
