/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 22:56:31 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/20 22:48:45 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static t_file	*ft_find_file(t_file **file_lst, int fd)
{
	t_file *tmp;

	tmp = *file_lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = ft_memalloc(sizeof(t_file))))
		return (NULL);
	tmp->fd = fd;
	ft_bzero(tmp->buff, BUFF_SIZE + 1);
	tmp->next = *file_lst;
	*file_lst = tmp;
	return (tmp);
}

static int		ft_strchr_i(char *str, char c)
{
	int index;

	if (str == NULL)
		return (-1);
	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

static int		ft_buff_to_line(char **line, char *buff)
{
	int		len;
	int		endline;
	char	*tmp;

	if (buff[0] == '\0')
		return (-1);
	endline = ft_strchr_i(buff, '\n');
	len = (endline == -1 ? ft_strlen(buff) : endline);
	if (*line == NULL && !(*line = ft_strnew(len)))
		return (-5);
	else if (*line == NULL)
		ft_strncpy(*line, buff, len);
	else
	{
		tmp = *line;
		if (!(*line = ft_strnew(ft_strlen(*line) + len)))
			return (-5);
		ft_strcpy(*line, tmp);
		ft_strncat(*line, buff, len);
		ft_strdel(&tmp);
	}
	ft_strcpy(buff, buff + len + 1);
	ft_bzero(buff + ft_strlen(buff), BUFF_SIZE - ft_strlen(buff));
	return (endline);
}

static int		ft_read_file(t_file *file, char **line)
{
	int ret;

	if ((ret = ft_buff_to_line(line, file->buff)) == -5)
		return (-1);
	else if (ret != -1)
		return (1);
	if ((ret = read(file->fd, file->buff, BUFF_SIZE)) <= 0)
	{
		if (ret == 0 && *line)
			return (1);
		return (ret);
	}
	return (ft_read_file(file, line));
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*file_lst = NULL;
	t_file			*file;

	if (line == NULL)
		return (-1);
	*line = NULL;
	if (!(file = ft_find_file(&file_lst, fd)))
		return (-1);
	return (ft_read_file(file, line));
}
