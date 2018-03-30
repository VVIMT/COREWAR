/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 21:05:19 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/23 00:12:43 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Return the corressponding size in the momory taken by the param type given
*/

int			ft_type_size(t_arg_type type, int index)
{
	if (type == T_REG)
		return (1);
	else if (type == T_DIR)
		return (g_op_tab[index].take_ram_addr ? IND_SIZE : DIR_SIZE);
	else if (type == T_IND)
		return (IND_SIZE);
	else
		return (0);
}

/*
** Return the size of the param
** WARNING: 0 <= param_nbr <= 2
*/

int			ft_get_param_size(t_process *process, unsigned int param_nbr,
																	int index)
{
	return (ft_type_size(ft_get_param_type(process, param_nbr), index));
}

/*
** Return the type of the param
** WARNING: 0 <= param_nbr <= 2
*/

t_arg_type	ft_get_param_type(t_process *process, unsigned int param_nbr)
{
	t_byte	param_code;

	param_code = (process->ocp
					>> ((2 - param_nbr) + 1) * 2) & 3;
	if (param_code == REG_CODE)
		return (T_REG);
	else if (param_code == DIR_CODE)
		return (T_DIR);
	else if (param_code == IND_CODE)
		return (T_IND);
	else
		return (0);
}

/*
** Return the param's value written in the memory
** WARNING: 0 <= param_nbr <= 2
*/

long long	ft_get_param_value(t_cor_env *cor_env, t_process *process,
											unsigned int param_nbr, int index)
{
	int				param_size;
	unsigned int	n;
	int				shift;

	n = 0;
	shift = 1 + g_op_tab[index].need_ocp;
	while (n < param_nbr && n < 3)
	{
		shift += ft_get_param_size(process, n, index);
		n++;
	}
	param_size = g_op_tab[index].need_ocp == 1 ?
					ft_get_param_size(process, n, index)
					: ft_type_size(g_op_tab[index].param_type[0], index);
	return (ft_read_mem(cor_env, ft_pc(process) + shift, param_size));
}

/*
** Return the real param's value: value of the register for REG,
** value of memory at the specify address for IND, and normal value for DIR
** WARNING: 0 <= param_nbr <= 2
*/

long long	ft_get_full_param_value(t_cor_env *cor_env, t_process *process,
											unsigned int param_nbr, int index)
{
	long long	param_value;
	t_arg_type	param_type;

	param_value = ft_get_param_value(cor_env, process, param_nbr, index);
	param_type = g_op_tab[index].need_ocp == 1 ?
		ft_get_param_type(process, param_nbr) : g_op_tab[index].param_type[0];
	if (param_type == T_REG)
		return (ft_read_register(process, param_value));
	else if (param_type == T_IND)
	{
		if (g_op_tab[index].restricted_addr)
			return (ft_read_mem(cor_env, ft_pc(process) +
										(param_value % IDX_MOD), DIR_SIZE));
		else
			return (ft_read_mem(cor_env,
									ft_pc(process) + param_value, DIR_SIZE));
	}
	else
		return (param_value);
}
