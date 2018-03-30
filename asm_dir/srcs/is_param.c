/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 20:45:26 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/22 22:31:53 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Returns 1 if the parameter is a register
*/

static int	ft_is_register(char *line)
{
	int	j;

	j = 2;
	if (line[0] == REGIST_CHAR && ft_isdigit(line[1]))
	{
		if (ft_isdigit(line[2]))
			j = 3;
		if (ft_iswhitespace(line[j]) || line[j] == SEPARATOR_CHAR || !line[j]
												|| line[j] == COMMENT_CHAR)
			return (1);
	}
	return (0);
}

/*
**	Returns 1 if the parameter is an indirect
*/

static int	ft_is_indirect(char *line)
{
	int	j;

	j = 1;
	if (ft_isdigit(line[0]) || line[0] == '-')
	{
		while (ft_isdigit(line[j]))
			j++;
	}
	else if (line[0] == LABEL_CHAR && ft_strrchr(LABEL_CHARS, line[j++]))
	{
		while (line[j] && ft_strrchr(LABEL_CHARS, line[j]))
			j++;
	}
	else
		return (0);
	if (ft_iswhitespace(line[j]) || line[j] == SEPARATOR_CHAR
										|| !line[j] || line[j] == COMMENT_CHAR)
		return (1);
	return (0);
}

/*
** Returns the type of the parameter written at `line+i`
** Or calls ft_error if there's no valid parameter
*/

t_arg_type	ft_param_type(t_asm_env *env, char *line, int i)
{
	if (ft_is_register(line + i))
		return (T_REG);
	else if (line[i] == DIRECT_CHAR && ft_is_indirect(line + i + 1))
		return (T_DIR);
	else if (ft_is_indirect(line + i))
		return (T_IND);
	else
	{
		ft_strdel(&line);
		ft_error(env, "Not a valid parameter", env->line_num, i + 1);
	}
	return (0);
}
