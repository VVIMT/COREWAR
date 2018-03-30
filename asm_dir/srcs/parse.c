/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinvimo <vinvimo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 21:30:52 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/16 22:17:30 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Returns the index in g_op_tab corresponding to the instruction
** If it's not an instruction, returns -1
*/

int			ft_is_instruction(char *line)
{
	int	n;

	n = 0;
	while (g_op_tab[n].opcode)
	{
		if (!ft_strncmp(line, g_op_tab[n].name, ft_strlen(g_op_tab[n].name))
					&& ft_iswhitespace(line[ft_strlen(g_op_tab[n].name)]))
			return (n);
		n++;
	}
	return (-1);
}

/*
** Returns 1 if it's a label and 0 if not
*/

static int	ft_is_label(char *line, int i)
{
	int save_i;

	save_i = i;
	while (line[i] != LABEL_CHAR && line[i])
	{
		if (!ft_strrchr(LABEL_CHARS, line[i]))
			return (0);
		i++;
	}
	return ((line[i] && save_i < i) ? 1 : 0);
}

/*
** Parse all the input file (except the header) and write the
** corresponding data to the output file
*/

void		ft_parse(t_asm_env *env)
{
	int		i;
	char	*line;
	int		n;

	while (ft_asm_gnl(env, env->fd_input, &line))
	{
		if ((i = ft_pass_space(env, &line)) == -1)
			break ;
		if ((n = ft_is_instruction(line + i)) >= 0 && n <= 16)
			ft_instruction_line(env, line, i + ft_strlen(g_op_tab[n].name), n);
		else if (ft_is_label(line, i))
			ft_label_line(env, line, i);
		else if (line[i] != COMMENT_CHAR)
		{
			ft_strdel(&line);
			ft_error(env, "Unexpected character", env->line_num, i + 1);
		}
		ft_strdel(&line);
	}
}
