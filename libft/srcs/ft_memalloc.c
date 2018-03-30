/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:12:29 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/21 19:17:45 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*x;
	size_t	i;

	if (!(x = (void *)malloc(sizeof(*x) * (size))))
	{
		ft_putstr_fd("Problem with memory allocation\n", 2);
		exit(1);
	}
	i = 0;
	while (i < size)
	{
		x[i] = 0;
		i++;
	}
	return (x);
}
