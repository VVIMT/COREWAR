/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 20:04:47 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/05 19:37:34 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** [DEBUG] Print all players info to help
*/

/*
** void	ft_print_players(t_cor_env *cor_env)
** {
** 	int n;
**
** 	n = 0;
** 	while (n < MAX_PLAYERS && cor_env->players[n].number)
** 	{
** 		ft_printf("\n = = = =\n");
** 		ft_printf("Name:		{red}%s{eoc}\n", cor_env->players[n].name);
** 		ft_printf("Num:		{yellow}%d{eoc}\n", cor_env->players[n].number);
** 		ft_printf("Comment:	{ldark}{italic}%s{eoc}\n",
** 												cor_env->players[n].comment);
** 		ft_printf("Size:		{cyan}%d{eoc}\n", cor_env->players[n].size);
** 		n++;
** 	}
** }
*/

/*
** [DEBUG] Print all process info to help
*/

/*
** void	ft_print_process(t_cor_env *cor_env)
** {
** 	int			j;
** 	t_process	*tmp_pro;
**
** 	tmp_pro = cor_env->process_lst;
** 	while (tmp_pro)
** 	{
** 		ft_printf("Process:\n");
** 		ft_printf("  {lgreen}live_nbr{eoc}:	{green}%d{eoc}\n",
** 															tmp_pro->live_nbr);
** 		ft_printf("  {lgreen}waiting_time{eoc}:	{green}%d{eoc}\n",
** 														tmp_pro->waiting_time);
** 		ft_printf("  {lgreen}PC{eoc}:		{green}%lld{eoc}\n",
**															ft_pc(tmp_pro));
** 		ft_printf("  {lgreen}carry{eoc}:	{green}%d{eoc}\n", tmp_pro->carry);
** 		ft_printf("  {lgreen}registers{eoc}:	[");
** 		j = 0;
** 		while (j < REG_NUMBER)
** 		{
** 			ft_printf("r%d: {green}%d{eoc}%s", j + 1,
** 				ft_read_register(tmp_pro, j + 1),
** 				(j + 1 == REG_NUMBER) ? "]\n" : ", ");
** 			j++;
** 		}
** 		tmp_pro = tmp_pro->next;
** 	}
** }
*/

/*
** Check if value of op.h has been changed
*/

void	ft_check_op_val(void)
{
	int	reg;
	int	dir;
	int	ind;

	reg = REG_SIZE > sizeof(long long);
	dir = DIR_SIZE > sizeof(long long);
	ind = IND_SIZE > sizeof(long long);
	if (reg || dir || ind)
	{
		ft_printf_fd(2, "{lred}error:{eoc} {lblack}{italic}%s%s%s%s \
larger than long long size (%d bytes){eoc}\n", reg == 1 ? "REG_SIZE " : "",
dir == 1 ? "DIR_SIZE " : "", ind == 1 ? "IND_SIZE " : "",
reg + dir + ind > 1 ? "are" : "is", sizeof(long long));
		exit(0);
	}
	else if (REG_SIZE != 4 || DIR_SIZE != REG_SIZE || IND_SIZE != 2)
		ft_printf("{lblack}{italic}Warning: REG_SIZE, DIR_SIZE or IND_SIZE \
have been change\nBe sure to use .cor file compiled with an asm configured \
with the same value\n{eoc}n");
}

/*
** Initializes the env_cor variable
*/

void	ft_init_env(t_cor_env *cor_env)
{
	int	n;

	n = 0;
	while (n < MAX_PLAYERS)
	{
		ft_bzero(cor_env->players[n].name, PROG_NAME_LENGTH + 1);
		ft_bzero(cor_env->players[n].comment, COMMENT_LENGTH + 1);
		cor_env->players[n].number = 0;
		cor_env->players[n].fd = 0;
		n++;
	}
	ft_bzero(cor_env->mem, MEM_SIZE);
	cor_env->process_lst = NULL;
	cor_env->dump_nbr = -1;
	cor_env->cycle = 0;
	cor_env->cycle_to_die = CYCLE_TO_DIE;
	cor_env->cycle_nbr_befor_check = CYCLE_TO_DIE - 1;
	cor_env->checks_nbr = 0;
	cor_env->total_live_nbr = 0;
	cor_env->last_player_live = NULL;
}

int		main(int argc, char *argv[])
{
	t_cor_env	cor_env;

	if (argc == 1)
	{
		ft_printf_fd(2, "{bright}Usage:{eoc} \
./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
		exit(0);
	}
	ft_check_op_val();
	ft_init_env(&cor_env);
	ft_parse_cmd(&cor_env, argc, argv);
	if (!cor_env.players[0].number)
	{
		ft_printf_fd(2, "{lred}No player{eoc} given\n");
		exit(1);
	}
	ft_init_game(&cor_env);
	ft_play_game(&cor_env);
	ft_quit(&cor_env, 0);
	return (0);
}
