/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 18:24:08 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/20 17:52:56 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Checks if all the procces have live
*/

static void	ft_check_live(t_cor_env *cor_env)
{
	t_process	*process;
	t_process	**prev_pro;

	process = cor_env->process_lst;
	prev_pro = &(cor_env->process_lst);
	while (process)
	{
		if (process->live_nbr == 0)
		{
			(*prev_pro) = process->next;
			ft_memdel((void **)&process);
			process = (*prev_pro);
		}
		else
		{
			process->live_nbr = 0;
			prev_pro = &((*prev_pro)->next);
			process = process->next;
		}
	}
}

/*
** Checks all Cycle related things
*/

void		ft_check_cycle(t_cor_env *cor_env)
{
	int			n;

	n = 0;
	if (cor_env->cycle > 1 && cor_env->cycle_nbr_befor_check <= 0)
	{
		ft_check_live(cor_env);
		(cor_env->checks_nbr)++;
		if (cor_env->total_live_nbr >= NBR_LIVE
		|| cor_env->checks_nbr >= MAX_CHECKS)
		{
			cor_env->cycle_to_die -= CYCLE_DELTA;
			cor_env->checks_nbr = 0;
		}
		cor_env->total_live_nbr = 0;
		cor_env->cycle_nbr_befor_check = cor_env->cycle_to_die;
	}
	(cor_env->cycle_nbr_befor_check)--;
}
