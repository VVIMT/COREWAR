/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_byte_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 04:49:00 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/23 00:52:22 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Pass long long nbr to negative if the smaller readed nbr is negative
*/

long long	ft_signed_nb(long long nbr, int size)
{
	long long one;
	long long o;

	one = -1;
	o = 1;
	if (size != sizeof(long long) && ((o << ((size * 8) - 1)) & nbr))
		return (nbr | (one << (size * 8)));
	return (nbr);
}

/*
** Returm a number of `nbr_size` bytes
*/

long long	ft_read_nb(t_byte *nbr, int nbr_size)
{
	long long	result;
	int			n;

	n = 0;
	nbr_size--;
	result = 0;
	while (nbr_size >= 0)
	{
		result = result | ((long long)nbr[n] << (nbr_size * 8));
		nbr_size--;
		n++;
	}
	return (result);
}

/*
** Write a nbr of `nbr_size` bytes
*/

void		ft_write_nb(t_byte *dest, int nbr_size, long long nbr)
{
	int	shift;
	int	n;

	shift = 8 * (nbr_size - 1);
	n = 0;
	while (shift >= 0)
	{
		dest[n] = nbr >> shift;
		n++;
		shift -= 8;
	}
}
