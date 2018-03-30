/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:10:30 by fmuller           #+#    #+#             */
/*   Updated: 2018/01/26 16:44:54 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

/*
** Verify that there is a player's file after the '-n' option
** and call ft_get_player()
*/

void		ft_after_n(t_cor_env *cor_env, t_cmd *cmd,
							int players_num[MAX_PLAYERS], int *next_player_num)
{
	cmd->i++;
	if (cmd->argc > cmd->i)
		ft_get_player(cor_env, cmd->argv[cmd->i], ft_player_num(cor_env,
												players_num, next_player_num));
	else
	{
		ft_printf_fd(2, "{cyan}-n {italic}nbr{eoc} option must be followed \
by a player\n");
		ft_quit(cor_env, 1);
	}
}

/*
** verify if the given number with the '-n' option is valid
*/

int			ft_player_num(t_cor_env *cor_env, int players_num[MAX_PLAYERS],
														int *next_player_num)
{
	int	n;
	int	num;

	if (!(*next_player_num))
		return (-1);
	n = 0;
	while (n < MAX_PLAYERS)
	{
		if (players_num[n] == *next_player_num)
		{
			num = *next_player_num;
			*next_player_num = 0;
			players_num[n] = 0;
			return (num);
		}
		n++;
	}
	if (*next_player_num > MAX_PLAYERS)
		ft_printf_fd(2, "Player's number must be between {cyan}1{eoc} \
and {cyan}%d{eoc}\n", MAX_PLAYERS);
	else
		ft_printf_fd(2, "There can't be {cyan}two players{eoc} %d\n",
															*next_player_num);
	ft_quit(cor_env, 1);
	return (42);
}

/*
** Read in a file, an int written in bing endian
*/

static int	ft_read_int_bg(int fd, int *nb)
{
	int		read_nb;
	int		ret;

	ret = read(fd, &read_nb, sizeof(int));
	if (ret == 4)
	{
		((char *)nb)[0] = read_nb >> 24;
		((char *)nb)[1] = read_nb >> 16;
		((char *)nb)[2] = read_nb >> 8;
		((char *)nb)[3] = read_nb;
	}
	else
		*nb = read_nb;
	return (ret);
}

/*
** initialise the player's struct
*/

static void	ft_init_player(t_cor_env *cor_env, t_player *player,
															char *file_name)
{
	int	magic;
	int	blank;

	if (ft_read_int_bg(player->fd, &magic) < 4 || magic != COREWAR_EXEC_MAGIC
	|| read(player->fd, player->name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH
	|| ft_read_int_bg(player->fd, &blank) < 4 || blank != 0
	|| ft_read_int_bg(player->fd, &(player->size)) < 4
	|| player->size > CHAMP_MAX_SIZE || player->size <= 0
	|| read(player->fd, player->comment, COMMENT_LENGTH) < COMMENT_LENGTH
	|| ft_read_int_bg(player->fd, &blank) < 4 || blank != 0)
	{
		if (player->size > CHAMP_MAX_SIZE)
			ft_printf_fd(2, "{bright}%s{eoc} is too long\
(max {cyan}%d octet{eoc})\n", file_name, CHAMP_MAX_SIZE);
		else
			ft_printf_fd(2, "{bright}%s{eoc}'s header is \
{lred}not well formated{eoc}\n", file_name);
		ft_quit(cor_env, 1);
	}
}

/*
** Parse the player's file name given and open it
*/

void		ft_get_player(t_cor_env *cor_env, char *file, int player_num)
{
	int	n;

	if (ft_strlen(file) < 5 || ft_strcmp(file + ft_strlen(file) - 4, ".cor"))
	{
		ft_printf_fd(2, "{bright}%s{eoc} is not a '{cyan}.cor{eoc}' file\n",
																		file);
		ft_quit(cor_env, 1);
	}
	n = 0;
	while (n < MAX_PLAYERS && cor_env->players[n].number != 0)
		n++;
	if (n >= MAX_PLAYERS)
	{
		ft_printf_fd(2, "There can't be more than {cyan}%d{eoc} players\n",
																MAX_PLAYERS);
		ft_quit(cor_env, 1);
	}
	if ((cor_env->players[n].fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf_fd(2, "{red}Failed{eoc} to open {bright}%s{eoc}\n", file);
		exit(1);
	}
	cor_env->players[n].number = player_num;
	ft_init_player(cor_env, &(cor_env->players[n]), file);
}
