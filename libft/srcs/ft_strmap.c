/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:20:44 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/20 19:10:28 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	size_t	i;

	i = 0;
	if (s && f)
	{
		if (!(str = (char *)ft_memalloc(sizeof(char) * (ft_strlen(s) + 1))))
			return (NULL);
		ft_strcpy(str, s);
		while (str[i])
		{
			str[i] = (*f)(str[i]);
			i++;
		}
		return (str);
	}
	return (NULL);
}
