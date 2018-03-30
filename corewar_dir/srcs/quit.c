/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:38:30 by fmuller           #+#    #+#             */
/*   Updated: 2018/01/26 16:43:50 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** A function to free vars, close files and exit the program from anywhere
** in the code
*/

void	ft_quit(t_cor_env *cor_env, int ret_value)
{
	int			n;
	t_process	*tmp_pro;

	n = 0;
	while (n < MAX_PLAYERS && cor_env->players[n].number)
	{
		if (cor_env->players[n].fd != 0)
			close(cor_env->players[n].fd);
		n++;
	}
	while (cor_env->process_lst)
	{
		tmp_pro = cor_env->process_lst->next;
		ft_memdel((void **)&(cor_env->process_lst));
		cor_env->process_lst = tmp_pro;
	}
	exit(ret_value);
}
