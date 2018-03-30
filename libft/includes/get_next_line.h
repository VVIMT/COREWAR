/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 22:56:46 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/03 02:44:47 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 100

typedef	struct	s_file
{
	int				fd;
	char			buff[BUFF_SIZE + 1];
	struct s_file	*next;
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
