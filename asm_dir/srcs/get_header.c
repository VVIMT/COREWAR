/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 06:29:38 by fmuller           #+#    #+#             */
/*   Updated: 2017/12/19 20:53:02 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Return the index of the next char that's not a space or a tab
** If there's not, go to the next line with ft_asm_gnl
*/

int			ft_pass_space(t_asm_env *asm_env, char **str)
{
	int i;

	i = 0;
	while (ft_iswhitespace((*str)[i]))
		i++;
	if (!(*str)[i])
	{
		ft_strdel(str);
		if (ft_asm_gnl(asm_env, asm_env->fd_input, str) != 1)
			return (-1);
		return (ft_pass_space(asm_env, str));
	}
	return (i);
}

static void	ft_parse_header2(t_asm_env *asm_env, char *line, int line_start)
{
	if (line[line_start] != COMMENT_CHAR)
	{
		ft_strdel(&line);
		ft_error(asm_env, "Syntax error, not header", asm_env->line_num,
																line_start + 1);
	}
}

/*
** Parse header
*/

static void	ft_parse_header(t_asm_env *asm_env)
{
	char	*line;
	int		line_start;
	int		type_name;
	int		type_comment;
	int		ret;

	type_name = 0;
	type_comment = 2;
	while ((!type_name || type_comment == 2) && (ret = ft_asm_gnl(asm_env,
											asm_env->fd_input, &line) == 1))
	{
		if ((line_start = ft_pass_space(asm_env, &line)) == -1)
			ft_error(asm_env, "Missing header part", asm_env->line_num, -1);
		if (!ft_strncmp(line + line_start, NAME_STR, ft_strlen(NAME_STR)))
			ft_get_string(asm_env, &line, line_start +
									ft_strlen(NAME_STR), &type_name);
		else if (!ft_strncmp(line + line_start, COM_STR, ft_strlen(COM_STR)))
			ft_get_string(asm_env, &line, line_start +
								ft_strlen(COM_STR), &type_comment);
		else
			ft_parse_header2(asm_env, line, line_start);
		ft_strdel(&line);
	}
	if (ret == 0)
		ft_error(asm_env, "Missing header part", asm_env->line_num, -1);
}

/*
** Initialise variables relatives to the header
*/

static void	ft_init_header(t_asm_env *asm_env)
{
	asm_env->magic[0] = 0x00;
	asm_env->magic[1] = 0xea;
	asm_env->magic[2] = 0x83;
	asm_env->magic[3] = 0xf3;
	ft_bzero(asm_env->prog_name, PROG_NAME_LENGTH);
	ft_bzero(asm_env->comment, COMMENT_LENGTH);
}

/*
** Checks header validity and stores it's content in variables
*/

void		ft_get_header(t_asm_env *asm_env)
{
	ft_init_header(asm_env);
	ft_parse_header(asm_env);
}
