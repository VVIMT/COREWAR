/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_buff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 01:03:58 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/07 00:08:36 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

/*
** Check if there's enough place in bin_buff to write 'size' octet
** If there isn't enough space, use realloc to make it
*/

void	ft_check_bin_buff(t_asm_env *env, unsigned int size)
{
	unsigned int	max_size;
	unsigned int	add_size;

	max_size = 0;
	add_size = 0;
	while (max_size < env->bin_size)
		max_size += BIN_BUFF_SIZE;
	if (env->bin_size + size > max_size)
	{
		while (env->bin_size + size > max_size + add_size)
			add_size += BIN_BUFF_SIZE;
		if (!(env->bin_buff = realloc(env->bin_buff, max_size + add_size)))
			ft_error(env, "Error with realloc", -1, -1);
		ft_bzero(env->bin_buff + env->bin_size,
										(max_size + add_size) - env->bin_size);
	}
}

/*
** write a nbr in `bin_buff`, in big_endian mode
** before, call ft_check_bin_buff
*/

void	ft_write_nb(t_asm_env *env, int nbr, int len)
{
	int	shift;

	shift = 8 * (len - 1);
	ft_check_bin_buff(env, len);
	while (len > 0)
	{
		(env->bin_buff)[env->bin_size] = nbr >> shift;
		env->bin_size++;
		len--;
		shift -= 8;
	}
}

/*
** write a nbr in `bin_buff` at the given address, in big_endian mode
** WARNING: write numbers in malloced parts of `bin_buff`
*/

void	ft_write_nb_addr(t_asm_env *env, int nbr, int len, unsigned int addr)
{
	int	shift;

	shift = 8 * (len - 1);
	while (len > 0)
	{
		(env->bin_buff)[addr] = nbr >> shift;
		addr++;
		len--;
		shift -= 8;
	}
}
