/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 19:20:56 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/05 22:44:49 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Initialise inst_array with pointer of function
** corresponding to each instruction
**
** WARNING: the function corresponding to the
** instruction MUST have te same index
*/

static void	ft_init_inst_array(void (*inst_array[16])(t_cor_env *cor_env,
												t_process *process, int index))
{
	inst_array[0] = ft_live;
	inst_array[1] = ft_ld;
	inst_array[2] = ft_st;
	inst_array[3] = ft_add;
	inst_array[4] = ft_sub;
	inst_array[5] = ft_and;
	inst_array[6] = ft_or;
	inst_array[7] = ft_xor;
	inst_array[8] = ft_zjmp;
	inst_array[9] = ft_ldi;
	inst_array[10] = ft_sti;
	inst_array[11] = ft_fork;
	inst_array[12] = ft_lld;
	inst_array[13] = ft_lldi;
	inst_array[14] = ft_lfork;
	inst_array[15] = ft_aff;
}

/*
** Announce the winner and dumped the memory
*/

static void	ft_end_game(t_cor_env *cor_env)
{
	if (cor_env->dump_nbr >= 0)
	{
		ft_print_mem(cor_env);
		if (cor_env->cycle != cor_env->dump_nbr)
			ft_printf("\n{lred}WARNING{eoc}: {italic}{lblack}dumped the last \
cycle (%d) before the end of the game{eoc}\n", cor_env->cycle);
		ft_printf("\n");
	}
	if (cor_env->cycle != cor_env->dump_nbr
										&& cor_env->last_player_live == NULL)
		ft_printf("No one {lred}won{eoc}, no player has {cyan}lived{eoc} \
during the game\n");
	else if (cor_env->cycle != cor_env->dump_nbr)
		ft_printf("Player {bright}%d{eoc}({bright}%s{eoc}) {lgreen}won{eoc}\n",
		cor_env->last_player_live->number, cor_env->last_player_live->name);
}

static void	ft_introduce_player(t_cor_env *cor_env)
{
	int			n;
	t_player	*player;

	n = 1;
	while (n <= MAX_PLAYERS)
	{
		if ((player = ft_find_player(cor_env, n)))
		{
			ft_printf("Player {cyan}%d{eoc}: {bright}%s{eoc}\n\
{lblack}%s{eoc}\n\n", player->number, player->name, player->comment);
		}
		n++;
	}
}

/*
** The principal loop to manage each cycle of the game
*/

void		ft_play_game(t_cor_env *cor_env)
{
	void	(*inst_array[16]) (t_cor_env *cor_env, t_process *process, int i);

	ft_init_inst_array(inst_array);
	ft_introduce_player(cor_env);
	while (cor_env->process_lst && cor_env->dump_nbr != cor_env->cycle)
	{
		ft_exec_instruction(cor_env, inst_array);
		ft_check_cycle(cor_env);
		(cor_env->cycle)++;
	}
	ft_end_game(cor_env);
}
