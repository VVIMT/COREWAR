/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 21:30:05 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/06 23:20:15 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Print an error before calling ft_quit
*/

void	ft_error(t_asm_env *asm_env, char *message, int line, int col)
{
	if (line != -1 && col != -1)
		ft_printf_fd(2, "%s:{bright}%d{eoc}:{bright}%d{eoc}: {bright,red}error\
{eoc}:  {italic}%s{eoc}\n\n", asm_env->file_name, line, col, message);
	else if (line != -1)
		ft_printf_fd(2, "%s:{bright}%d{eoc}: {bright,red}error{eoc}:  {italic}\
%s{eoc}\n\n", asm_env->file_name, line, message);
	else
		ft_printf_fd(2, "%s {bright,red}error{eoc}:  {italic}%s{eoc}\n\n",
												asm_env->file_name, message);
	ft_quit(asm_env, 1);
}

/*
** A function to free vars, close files and exit the program from anywhere
** in the code
*/

void	ft_quit(t_asm_env *asm_env, int ret_value)
{
	t_label *tmp_lst;

	if (asm_env->fd_input != -1)
		close(asm_env->fd_input);
	ft_memdel((void **)&(asm_env->bin_buff));
	tmp_lst = asm_env->label_lst;
	while (tmp_lst)
	{
		ft_strdel(&(tmp_lst->name));
		ft_memdel((void **)&(tmp_lst->param_addr));
		ft_memdel((void **)&(tmp_lst->param_size));
		ft_memdel((void **)&(tmp_lst->inst_addr));
		asm_env->label_lst = asm_env->label_lst->next;
		if (tmp_lst)
			free(tmp_lst);
		tmp_lst = asm_env->label_lst;
	}
	exit(ret_value);
}
