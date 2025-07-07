/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:01:31 by opopov            #+#    #+#             */
/*   Updated: 2024/11/26 18:15:00 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	*copy_word(char const *start, size_t len)
{
	size_t	i;
	char	*word;

	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static int	main_calc(char const *s, char c, char **result)
{
	char const	*start;
	int			index;

	index = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		if (start != s)
		{
			result[index] = copy_word(start, s - start);
			if (!result[index])
			{
				while (index > 0)
					free(result[--index]);
				free(result);
				return (-1);
			}
			index++;
		}
	}
	return (index);
}

char	**ft_split(char const *s, char c)
{
	int			words;
	int			index;
	char		**result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = main_calc(s, c, result);
	if (index == -1)
		return (NULL);
	result[index] = NULL;
	return (result);
}
