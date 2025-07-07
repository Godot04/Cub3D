/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:48:54 by opopov            #+#    #+#             */
/*   Updated: 2024/11/11 13:58:30 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int argument)
{
	if ((argument >= 65 && argument <= 90)
		|| (argument >= 97 && argument <= 122)
		|| (argument >= 48 && argument <= 57))
	{
		return (8);
	}
	else
	{
		return (0);
	}
}
