/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 05:05:24 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/23 00:50:31 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** If the given opcode exist, return it's index, if not return 0
*/

int			ft_is_instruction(int opcode)
{
	int	n;

	n = 0;
	while (n < 16)
	{
		if (opcode == g_op_tab[n].opcode)
			return (n);
		n++;
	}
	return (-1);
}

/*
** Return 1 if the ocp is valid, 0 if not
*/

static int	ft_is_instruction_valid(t_cor_env *cor_env, t_process *process,
																	int index)
{
	int			n;
	t_arg_type	type;
	long long	reg_nbr;

	if (g_op_tab[index].need_ocp)
	{
		n = 0;
		while (n < g_op_tab[index].param_nbr)
		{
			if (!((type = ft_get_param_type(process, n))
								& g_op_tab[index].param_type[n]))
				return (0);
			if (type == T_REG
			&& (((reg_nbr = ft_get_param_value(cor_env, process, n, index)) < 1)
				|| reg_nbr > REG_NUMBER))
				return (0);
			n++;
		}
	}
	else if (g_op_tab[index].param_type[0] == T_REG
		&& (((reg_nbr = ft_get_param_value(cor_env, process, first, index)) < 1)
			|| reg_nbr > REG_NUMBER))
		return (0);
	return (1);
}

/*
** Execute the current instruction of each process of each players
*/

void		ft_exec_instruction(t_cor_env *cor_env, void (*inst_array[16])
						(t_cor_env *cor_env, t_process *process, int index))
{
	t_process	*pro;

	pro = cor_env->process_lst;
	while (pro)
	{
		if (pro->index == -1)
			ft_set_waiting_time(cor_env, pro);
		if (pro->waiting_time)
			(pro->waiting_time)--;
		if (!pro->waiting_time)
		{
			if (pro->index != -1)
			{
				pro->ocp = ft_read_mem(cor_env, ft_pc(pro) + 1, 1);
				if (ft_is_instruction_valid(cor_env, pro, pro->index))
					inst_array[pro->index](cor_env, pro, pro->index);
				if (inst_array[pro->index] != ft_zjmp)
					ft_advance_pc(pro, pro->index);
				pro->index = -1;
			}
			else
				ft_add_pc(pro, 1);
		}
		pro = pro->next;
	}
}
