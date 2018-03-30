/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:05:39 by fmuller           #+#    #+#             */
/*   Updated: 2018/01/16 17:34:30 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Return 1 if the given string is only composed of number
** and 0 if not
*/

static int	ft_is_str_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** Parse option like '-dump' and '-n'
*/

static void	ft_get_option(t_cor_env *cor_env, t_cmd *cmd, int *target)
{
	cmd->i++;
	if (cmd->argc > cmd->i && ft_is_str_alnum(cmd->argv[cmd->i]))
		*target = ft_atoi(cmd->argv[cmd->i]);
	else
	{
		ft_printf_fd(2, "{cyan}%s{eoc} option must be followed by a number\n",
														cmd->argv[cmd->i - 1]);
		ft_quit(cor_env, 1);
	}
}

/*
** Init players_num array with all the num that players
** can have, base on MAX_PLAYERS
*/

static void	ft_init_players_num(int players_num[MAX_PLAYERS])
{
	int	n;

	n = 0;
	while (n < MAX_PLAYERS)
	{
		players_num[n] = n + 1;
		n++;
	}
}

/*
** Give a num to players who do not have one yet
*/

static void	ft_give_num(t_cor_env *cor_env, int players_num[MAX_PLAYERS])
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (n < MAX_PLAYERS)
	{
		if ((cor_env->players[n].number) == -1)
		{
			while (!players_num[i] && i < MAX_PLAYERS)
				i++;
			cor_env->players[n].number = players_num[i];
			players_num[i] = 0;
		}
		n++;
	}
}

/*
** Parse the command to call corewar
*/

void		ft_parse_cmd(t_cor_env *cor_env, int argc, char *argv[])
{
	t_cmd	cmd;
	int		players_num[MAX_PLAYERS];
	int		next_player_num;

	cmd.i = 1;
	cmd.argc = argc;
	cmd.argv = argv;
	ft_init_players_num(players_num);
	next_player_num = 0;
	while (cmd.i < cmd.argc)
	{
		if (!ft_strcmp(cmd.argv[cmd.i], "-dump"))
			ft_get_option(cor_env, &cmd, &(cor_env->dump_nbr));
		else if (!ft_strcmp(cmd.argv[cmd.i], "-n"))
		{
			ft_get_option(cor_env, &cmd, &next_player_num);
			ft_after_n(cor_env, &cmd, players_num, &next_player_num);
		}
		else
			ft_get_player(cor_env, cmd.argv[cmd.i],
						ft_player_num(cor_env, players_num, &next_player_num));
		cmd.i++;
	}
	ft_give_num(cor_env, players_num);
}
