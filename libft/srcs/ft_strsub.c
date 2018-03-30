/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:23:12 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/20 19:10:41 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;

	if (!s)
		return (NULL);
	if (!(d = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(d, len + 1);
	i = 0;
	while (i < len && s[start + i])
	{
		d[i] = s[start + i];
		i++;
	}
	return (d);
}
