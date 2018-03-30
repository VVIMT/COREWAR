/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:27:37 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/22 22:32:28 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Returns the index where the next parameter is written in `line`
*/

static int		ft_next_param(t_asm_env *env, char *l, int i, int param_nu)
{
	if (param_nu != 0)
	{
		while (!ft_iswhitespace(l[i]) && l[i] != SEPARATOR_CHAR && l[i])
			i++;
	}
	while (ft_iswhitespace(l[i]))
		i++;
	if (param_nu != 0)
	{
		if (l[i] == SEPARATOR_CHAR)
			i++;
		else
		{
			ft_strdel(&l);
			ft_error(env, "Missing the SEPARATOR_CHAR", env->line_num, i + 1);
		}
	}
	while (ft_iswhitespace(l[i]))
		i++;
	if (!l[i])
	{
		ft_strdel(&l);
		ft_error(env, "Missing parameter", env->line_num, i + 1);
	}
	return (i);
}

/*
** Writes the given parameter to the .cor file
*/

static void		ft_write_param(t_asm_env *env, char *line,
										t_arg_type param_type, int inst_num)
{
	int	size;

	size = (param_type == T_REG) ? 1 : IND_SIZE;
	if (param_type == T_DIR)
		size = (g_op_tab[inst_num].take_ram_addr) ? IND_SIZE : DIR_SIZE;
	if (param_type == T_DIR || param_type == T_REG)
		line++;
	if (line[0] == LABEL_CHAR)
		ft_add_label_dest(env, ++line, size);
	else
		ft_write_nb(env, ft_atoi(line), size);
}

/*
** Completes the ocp
*/

static void		ft_write_ocp(unsigned char *ocp, t_arg_type param_type,
																int param_num)
{
	if (param_type == T_REG)
		ocp[0] = ocp[0] | (REG_CODE << (6 - (param_num * 2)));
	else if (param_type == T_DIR)
		ocp[0] = ocp[0] | (DIR_CODE << (6 - (param_num * 2)));
	else if (param_type == T_IND)
		ocp[0] = ocp[0] | (IND_CODE << (6 - (param_num * 2)));
}

/*
** Returns the index of the last character of the last parameter
*/

static int		ft_find_end(char *line, int i)
{
	while (!ft_iswhitespace(line[i]) && line[i] != SEPARATOR_CHAR
							&& line[i] != COMMENT_CHAR && line[i])
		i++;
	return (i - 1);
}

/*
** Writes an instruction and its parameters to the output file
*/

void			ft_instruction_line(t_asm_env *env, char *line, int i,
																int inst_num)
{
	int				param_num;
	t_arg_type		param_type;
	unsigned int	ocp_addr;

	env->instruction_addr = env->bin_size;
	ft_write_nb(env, g_op_tab[inst_num].opcode, 1);
	ocp_addr = env->bin_size;
	if (g_op_tab[inst_num].need_ocp)
		ft_write_nb(env, 0, 1);
	param_num = 0;
	while (param_num < g_op_tab[inst_num].param_nbr)
	{
		i = ft_next_param(env, line, i, param_num);
		if (!((param_type = ft_param_type(env, line, i)) &
									g_op_tab[inst_num].param_type[param_num]))
		{
			ft_strdel(&line);
			ft_error(env, "Wrong parameter type", env->line_num, i + 1);
		}
		if (g_op_tab[inst_num].need_ocp)
			ft_write_ocp(env->bin_buff + ocp_addr, param_type, param_num);
		ft_write_param(env, line + i, param_type, inst_num);
		param_num++;
	}
	ft_check_endline(env, line, ft_find_end(line, i));
}
