/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 00:00:50 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/20 22:06:42 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_sti(t_cor_env *cor_env, t_process *process, int index)
{
	long long	nbr;
	int			addr;

	nbr = ft_read_register(process, ft_get_param_value(cor_env, process, first,
																	index));
	addr = ft_get_full_param_value(cor_env, process, second, index)
			+ ft_get_full_param_value(cor_env, process, third, index);
	ft_write_mem(cor_env, ft_pc(process) + (addr % IDX_MOD), DIR_SIZE, nbr);
}

void		ft_fork(t_cor_env *cor_env, t_process *process, int index)
{
	long long	new_pc;
	t_process	*new;

	new_pc = ft_pc(process);
	new_pc += (ft_get_param_value(cor_env, process, first, index) % IDX_MOD);
	new = ft_dup_process(cor_env, process, new_pc);
	ft_set_waiting_time(cor_env, new);
	new->next = cor_env->process_lst;
	cor_env->process_lst = new;
}

void		ft_lld(t_cor_env *cor_env, t_process *process, int index)
{
	long long nbr;

	nbr = ft_get_full_param_value(cor_env, process, first, index);
	nbr = nbr >> (2 * 8);
	ft_write_register(process, ft_get_param_value(cor_env, process, second,
																index), nbr);
	process->carry = nbr == 0 ? 1 : 0;
}

void		ft_lldi(t_cor_env *cor_env, t_process *process, int index)
{
	long long	addr;
	long long	nbr;

	addr = ft_get_full_param_value(cor_env, process, first, index)
		+ ft_get_full_param_value(cor_env, process, second, index);
	nbr = ft_read_mem(cor_env, ft_pc(process) + addr, REG_SIZE);
	ft_write_register(process, ft_get_param_value(cor_env, process, third,
																index), nbr);
	process->carry = nbr == 0 ? 1 : 0;
}

void		ft_lfork(t_cor_env *cor_env, t_process *process, int index)
{
	long long	new_pc;
	t_process	*new;

	new_pc = ft_pc(process);
	new_pc += (ft_get_param_value(cor_env, process, first, index));
	new = ft_dup_process(cor_env, process, new_pc);
	ft_set_waiting_time(cor_env, new);
	new->next = cor_env->process_lst;
	cor_env->process_lst = new;
}
