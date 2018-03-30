/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 18:04:44 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/20 19:47:48 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	*ft_nbdup(int lenght, ...)
{
	va_list	ap;
	int		*tab;
	int		n;
	int		nbr;

	n = 0;
	if (!(tab = ft_memalloc(lenght * sizeof(int))))
		return (NULL);
	va_start(ap, lenght);
	while (n < lenght)
	{
		nbr = va_arg(ap, int);
		tab[n] = nbr;
		n++;
	}
	va_end(ap);
	return (tab);
}
