/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 23:47:24 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/23 00:58:15 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Read `size` byte frome memory
*/

long long	ft_read_mem(t_cor_env *cor_env, int addr, int size)
{
	long long result;

	result = 0;
	addr = addr % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	if (addr + size > MEM_SIZE)
	{
		result = ft_read_nb(cor_env->mem + addr, MEM_SIZE - addr)
										<< ((size - (MEM_SIZE - addr)) * 8);
		result = result | ft_read_nb(cor_env->mem, size - (MEM_SIZE - addr));
	}
	else
		result = ft_read_nb(cor_env->mem + addr, size);
	return (ft_signed_nb(result, size));
}

/*
** Write `size` byte frome memory
*/

void		ft_write_mem(t_cor_env *cor_env, int addr, int size, long long nbr)
{
	addr = addr % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	if (addr + size > MEM_SIZE)
	{
		ft_write_nb(cor_env->mem + addr, MEM_SIZE - addr, nbr >>
											((size - (MEM_SIZE - addr)) * 8));
		ft_write_nb(cor_env->mem, size - (MEM_SIZE - addr), nbr);
	}
	else
		ft_write_nb(cor_env->mem + addr, size, nbr);
}

/*
** Print the memory
*/

void		ft_print_mem(t_cor_env *cor_env)
{
	int	n;

	n = 0;
	while (n < MEM_SIZE)
	{
		if (!(n % 32))
			ft_printf("\n");
		if (ft_read_mem(cor_env, n, 1))
			ft_printf("%02hhx ", ft_read_mem(cor_env, n, 1));
		else
			ft_printf("{lblack}%02hhx{eoc} ", ft_read_mem(cor_env, n, 1));
		n++;
	}
	ft_printf("\n");
}
