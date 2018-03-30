/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 03:09:03 by fmuller           #+#    #+#             */
/*   Updated: 2017/12/19 20:48:08 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Checks if this header part has not been already been read
** and if there's nothing between cmd and string
*/

static void	ft_get_string_error(t_asm_env *asm_env, char **line, int *i,
																	int type)
{
	if (type == 1 || type == 3)
	{
		ft_strdel(line);
		ft_error(asm_env, "Already got that header part", asm_env->line_num,
																		-1);
	}
	while (ft_iswhitespace((*line)[*i]))
		(*i)++;
	if ((*line)[*i] != '"')
	{
		ft_strdel(line);
		ft_error(asm_env, "Syntax error, not a string", asm_env->line_num, *i +
																			1);
	}
	(*i)++;
}

/*
** Return the index of the end of the string
*/

static int	ft_find_end(char *line, int i)
{
	while (line[i] != '"' && line[i])
		i++;
	return (i);
}

/*
** Check if there's nothing after the string
*/

void		ft_check_endline(t_asm_env *asm_env, char *line, int end)
{
	if (line[end])
		end++;
	while (line[end])
	{
		if (line[end] == COMMENT_CHAR)
			break ;
		else if (!ft_iswhitespace(line[end]))
		{
			ft_strdel(&line);
			ft_error(asm_env, "Unexpected character", asm_env->line_num,
																	end + 1);
		}
		end++;
	}
}

/*
** Verifies if there's enough space in prog_name or comment
*/

static void	ft_check_len(t_asm_env *asm_env, int len, char *line, int type)
{
	if ((ft_strlen((type == 0) ? asm_env->prog_name : asm_env->comment) + len)
						> ((type == 0) ? PROG_NAME_LENGTH : COMMENT_LENGTH))
	{
		ft_strdel(&line);
		ft_error(asm_env, "String too long (128 max)", asm_env->line_num, -1);
	}
}

/*
** Stores the string of .name or .comment
*/

void		ft_get_string(t_asm_env *asm_env, char **line, int i, int *type)
{
	int	end;

	ft_get_string_error(asm_env, line, &i, *type);
	end = 0;
	while ((*line)[end] != '"')
	{
		if (!(*line)[end])
		{
			i = 0;
			ft_check_len(asm_env, 1, *line, *type);
			ft_strcat(((*type == 0) ? asm_env->prog_name : asm_env->comment),
																		"\n");
			ft_strdel(line);
			if (ft_asm_gnl(asm_env, asm_env->fd_input, line) == 0)
				ft_error(asm_env, "Header string not ended", asm_env->line_num,
																		i + 1);
		}
		end = ft_find_end(*line, i);
		ft_check_len(asm_env, end - i, *line, *type);
		ft_strncat(((*type == 0) ? asm_env->prog_name : asm_env->comment),
														*line + i, end - i);
	}
	ft_check_endline(asm_env, *line, end);
	(*type)++;
}
