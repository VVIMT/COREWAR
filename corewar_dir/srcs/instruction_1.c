/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:44:38 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/03 04:30:36 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_live(t_cor_env *cor_env, t_process *process, int index)
{
	int			player_nbr;
	t_player	*player;

	player_nbr = ft_get_param_value(cor_env, process, first, index);
	player = ft_find_player(cor_env, player_nbr);
	if (player != NULL)
	{
		cor_env->last_player_live = player;
		ft_printf("A process shows that player %d ({bright}%s{eoc}) is alive\n"
						, player_nbr, (player == NULL) ? "" : player->name);
	}
	(process->live_nbr)++;
	(cor_env->total_live_nbr)++;
}

void	ft_ld(t_cor_env *cor_env, t_process *process, int index)
{
	long long nbr;

	nbr = ft_get_full_param_value(cor_env, process, first, index);
	ft_write_register(process, ft_get_param_value(cor_env, process, second,
																index), nbr);
	process->carry = nbr == 0 ? 1 : 0;
}

void	ft_st(t_cor_env *cor_env, t_process *process, int index)
{
	long long	nbr;

	nbr = ft_get_full_param_value(cor_env, process, first, index);
	if (ft_get_param_type(process, second) == T_REG)
		ft_write_register(process, ft_get_param_value(cor_env, process, second,
																index), nbr);
	else
		ft_write_mem(cor_env, ft_pc(process) + (ft_get_param_value(cor_env,
							process, second, index) % IDX_MOD), REG_SIZE, nbr);
}

void	ft_add(t_cor_env *cor_env, t_process *process, int index)
{
	long long	nbr;

	nbr = ft_get_full_param_value(cor_env, process, first, index);
	nbr = nbr + ft_get_full_param_value(cor_env, process, second, index);
	ft_write_register(process, ft_get_param_value(cor_env, process, third,
																index), nbr);
	process->carry = nbr == 0 ? 1 : 0;
}

void	ft_sub(t_cor_env *cor_env, t_process *process, int index)
{
	long long	nbr;

	nbr = ft_get_full_param_value(cor_env, process, first, index);
	nbr = nbr - ft_get_full_param_value(cor_env, process, second, index);
	ft_write_register(process, ft_get_param_value(cor_env, process, third,
																index), nbr);
	process->carry = nbr == 0 ? 1 : 0;
}
