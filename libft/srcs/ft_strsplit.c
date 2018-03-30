/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:22:38 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/20 19:10:35 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	int	ft_size(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static	int	ft_word(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] && s[i] == c)
				i++;
			i--;
			j++;
		}
		i++;
	}
	return (j);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**d;
	size_t	i;
	size_t	index;

	if (!s)
		return (NULL);
	if (!(d = (char**)ft_memalloc(sizeof(*d) * (ft_word(s, c) + 1))))
		return (NULL);
	index = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(d[index] = ft_strsub(s, i, ft_size((s + i), c))))
				return (NULL);
			index++;
			i = i + ft_size((s + i), c);
		}
		else
			i++;
	}
	d[index] = NULL;
	return (d);
}
