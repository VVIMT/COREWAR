/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 05:00:22 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/20 22:34:51 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Short named function to get the pc value
*/

long long	ft_pc(t_process *process)
{
	return (ft_signed_nb(ft_read_nb(process->pc, REG_SIZE), REG_SIZE));
}

/*
** Add value to the process's pc
*/

void		ft_add_pc(t_process *process, long long add)
{
	long long	new_pc;

	new_pc = (ft_pc(process) + add) % MEM_SIZE;
	if (new_pc < 0)
		new_pc += MEM_SIZE;
	ft_write_nb(process->pc, REG_SIZE, new_pc);
}

/*
** Advance the pc of the number of byte given in the ocp
*/

void		ft_advance_pc(t_process *process, int index)
{
	int	n;
	int	add;

	if (g_op_tab[index].need_ocp)
	{
		add = 1;
		n = 0;
		while (n < g_op_tab[index].param_nbr)
		{
			add += ft_get_param_size(process, n, index);
			n++;
		}
	}
	else
		add = ft_type_size(g_op_tab[index].param_type[0], index);
	ft_add_pc(process, 1 + add);
}

/*
** Set the waiting_time if the process's pc is pointing to an instruction
*/

void		ft_set_waiting_time(t_cor_env *cor_env, t_process *process)
{
	process->index = ft_is_instruction(ft_read_mem(cor_env, ft_pc(process), 1));
	if (process->index != -1)
		process->waiting_time = g_op_tab[process->index].cycle_nbr;
	else
		process->waiting_time = 0;
}

/*
** Duplicate a process
*/

t_process	*ft_dup_process(t_cor_env *cor_env, t_process *src,
															long long pc_val)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
	{
		ft_printf_fd(2, "{lred}error{eoc}:{italic}can't malloc process{eoc}\n");
		ft_quit(cor_env, 1);
	}
	*new = *src;
	pc_val = pc_val % MEM_SIZE;
	if (pc_val < 0)
		pc_val += MEM_SIZE;
	ft_write_register(new, PC, pc_val);
	return (new);
}
