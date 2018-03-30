/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:35:29 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/05 19:37:54 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Return the player corresponding to the given player number
*/

t_player			*ft_find_player(t_cor_env *cor_env, int number)
{
	int	n;

	n = 0;
	while (n < MAX_PLAYERS && cor_env->players[n].number)
	{
		if (cor_env->players[n].number == number)
			return (&(cor_env->players[n]));
		n++;
	}
	return (NULL);
}

/*
** Create a first process and return it
*/

static t_process	*ft_create_first_process(t_cor_env *cor_env, int number,
															long long pc_val)
{
	t_process	*new_process;

	if (!(new_process = ft_memalloc(sizeof(t_process))))
	{
		ft_printf_fd(2, "{lred}error{eoc}:{italic}can't malloc process{eoc}\n");
		ft_quit(cor_env, 1);
	}
	ft_bzero(new_process->registers, REG_SIZE * REG_NUMBER);
	ft_write_register(new_process, 1, number);
	ft_write_register(new_process, PC, pc_val);
	new_process->carry = 0;
	ft_set_waiting_time(cor_env, new_process);
	new_process->live_nbr = 0;
	new_process->next = NULL;
	return (new_process);
}

/*
** Return the total number of players
*/

static int			ft_number_of_players(t_cor_env *cor_env)
{
	int	n;

	n = 0;
	while (n < MAX_PLAYERS && cor_env->players[n].number)
		n++;
	return (n);
}

/*
** Copy champion code to mem
*/

static long long	ft_copy_champ(t_cor_env *cor_env, t_player *player,
														int valid_player_nbr)
{
	long long	shift;
	int			nbr_of_players;

	nbr_of_players = ft_number_of_players(cor_env);
	shift = (valid_player_nbr - 1) * (MEM_SIZE / nbr_of_players);
	if (CHAMP_MAX_SIZE * nbr_of_players > MEM_SIZE)
	{
		ft_printf_fd(2, "Memory too small for as many players \
{lblack}({italic}the memory size is defined in op.h, with MEM_SIZE){eoc}\n");
		ft_quit(cor_env, 1);
	}
	if (read(player->fd, cor_env->mem + shift, player->size) < player->size
	|| read(player->fd, cor_env->mem, player->size) != 0)
	{
		ft_printf_fd(2, "{bright}%s{eoc} champion is {lred}not well \
formated{eoc}\n", player->name);
		ft_quit(cor_env, 1);
	}
	return (shift);
}

/*
** Initialise the game, copy champ in mem and
** create first process for each player
*/

void				ft_init_game(t_cor_env *cor_env)
{
	int			nbr;
	int			valid_player_nbr;
	t_process	*tmp_pro;
	t_player	*player;

	nbr = 1;
	valid_player_nbr = 0;
	while (nbr <= MAX_PLAYERS)
	{
		if ((player = ft_find_player(cor_env, nbr)))
		{
			valid_player_nbr++;
			tmp_pro = cor_env->process_lst;
			cor_env->process_lst = ft_create_first_process(cor_env,
	player->number, ft_copy_champ(cor_env, player, valid_player_nbr));
			cor_env->process_lst->next = tmp_pro;
		}
		nbr++;
	}
}
