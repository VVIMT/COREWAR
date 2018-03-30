/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 20:17:03 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/23 01:02:44 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Return the number stored in the `reg_nbr` register
** or in the pc if `reg_nbr` is equal to PC (= -1)
*/

long long	ft_read_register(t_process *process, int reg_nbr)
{
	if (reg_nbr >= 1 && reg_nbr <= REG_NUMBER)
		return (ft_signed_nb(ft_read_nb(process->registers + ((reg_nbr - 1)
											* REG_SIZE), REG_SIZE), REG_SIZE));
	else if (reg_nbr == PC)
		return (ft_signed_nb(ft_read_nb(process->pc, REG_SIZE), REG_SIZE));
	return (0);
}

/*
** Write `nbr` to the `reg_nbr` register
** or to the pc if `reg_nbr` is equal to PC (= -1)
*/

void		ft_write_register(t_process *process, int reg_nbr, long long nbr)
{
	if (reg_nbr >= 1 && reg_nbr <= REG_NUMBER)
		ft_write_nb(process->registers + ((reg_nbr - 1) * REG_SIZE), REG_SIZE,
																		nbr);
	else if (reg_nbr == PC)
		return (ft_write_nb(process->pc, REG_SIZE, nbr));
}
