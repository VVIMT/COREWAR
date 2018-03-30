/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:57:23 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/23 00:35:02 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_and(t_cor_env *cor_env, t_process *process, int index)
{
	long long result;

	result = ft_get_full_param_value(cor_env, process, first, index)
					& ft_get_full_param_value(cor_env, process, second, index);
	ft_write_register(process, ft_get_param_value(cor_env, process, third,
																index), result);
	process->carry = result == 0 ? 1 : 0;
}

void	ft_or(t_cor_env *cor_env, t_process *process, int index)
{
	long long result;

	result = ft_get_full_param_value(cor_env, process, first, index)
				| ft_get_full_param_value(cor_env, process, second, index);
	ft_write_register(process,
				ft_get_param_value(cor_env, process, third, index), result);
	process->carry = result == 0 ? 1 : 0;
}

void	ft_xor(t_cor_env *cor_env, t_process *process, int index)
{
	long long result;

	result = ft_get_full_param_value(cor_env, process, first, index)
				^ ft_get_full_param_value(cor_env, process, second, index);
	ft_write_register(process,
				ft_get_param_value(cor_env, process, third, index), result);
	process->carry = result == 0 ? 1 : 0;
}

void	ft_zjmp(t_cor_env *cor_env, t_process *process, int index)
{
	if (process->carry)
		ft_add_pc(process, (ft_get_param_value(cor_env, process, first, index)
																	% IDX_MOD));
	else
		ft_advance_pc(process, index);
}

void	ft_ldi(t_cor_env *cor_env, t_process *process, int index)
{
	long long	addr;
	long long	nbr;

	addr = ft_get_full_param_value(cor_env, process, first, index)
		+ ft_get_full_param_value(cor_env, process, second, index);
	nbr = ft_read_mem(cor_env, ft_pc(process) + (addr % IDX_MOD), REG_SIZE);
	ft_write_register(process, ft_get_param_value(cor_env, process, third,
																index), nbr);
}
