/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 06:05:10 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/06 23:42:48 by vinvimo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_bigendian_int(char *dst, int nbr)
{
	dst[0] = nbr >> 24;
	dst[1] = nbr >> 16;
	dst[2] = nbr >> 8;
	dst[3] = nbr;
	return (dst);
}

/*
** Write all to the output file
** (magic, prog name, prog size, prg comment and the buff)
*/

void		ft_write_output(t_asm_env *asm_env, int fd_output,
														char *output_file_name)
{
	char	str_nb[4];

	write(fd_output, asm_env->magic, MAGIC_LENGTH);
	write(fd_output, asm_env->prog_name, PROG_NAME_LENGTH);
	write(fd_output, ft_bigendian_int(str_nb, 0), sizeof(int));
	write(fd_output, ft_bigendian_int(str_nb, asm_env->bin_size), sizeof(int));
	write(fd_output, asm_env->comment, COMMENT_LENGTH);
	write(fd_output, ft_bigendian_int(str_nb, 0), sizeof(int));
	write(fd_output, asm_env->bin_buff, asm_env->bin_size);
	ft_printf("{green}Writing output program to {bright}%s{eoc}\n",
															output_file_name);
}
