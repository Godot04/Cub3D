/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:44:47 by opopov            #+#    #+#             */
/*   Updated: 2024/11/27 12:20:17 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstnew(void *content)
{
	t_list *lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	(*lst).content = content;
	(*lst).next = NULL;
}
