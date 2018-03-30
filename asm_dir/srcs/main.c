/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:56:24 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/20 22:21:13 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include <fcntl.h>

/*
** Call get_next_line, but increment line before
*/

int			ft_asm_gnl(t_asm_env *asm_env, const int fd, char **line)
{
	int	ret;

	ret = get_next_line(fd, line);
	if (ret == 1)
		asm_env->line_num++;
	else if (ret == -1)
		ft_error(asm_env, "Error with get_next_line", asm_env->line_num, -1);
	return (ret);
}

/*
** Write the label address after parsing
*/

void		ft_put_addr(t_asm_env *env)
{
	t_label	*lst;
	int		i;

	lst = env->label_lst;
	while (lst)
	{
		if (lst->def_addr == -1)
		{
			ft_printf_fd(2, "%s {bright,red}error{eoc}: {italic}\"{bright}%s\
{eoc}{italic}\" label is undefined{eoc}\n\n", env->file_name, lst->name);
			ft_quit(env, 1);
		}
		i = -1;
		while (++i < lst->tab_size)
			ft_write_nb_addr(env, (lst->def_addr - lst->inst_addr[i]),
									lst->param_size[i], lst->param_addr[i]);
		lst = lst->next;
	}
}

/*
** Function to open .s file and check for some error in the filename given
*/

static int	ft_open_file(int argc, char const *argv[])
{
	int	fd;

	if (argc != 2)
	{
		if (argc < 2)
			ft_printf_fd(2,
					"{bright}Usage:{eoc} ./asm <sourcefile{cyan}.s{eoc}>\n");
		if (argc > 2)
			ft_printf_fd(2, "You can't pass more than {cyan}one file{eoc}\n");
		exit(1);
	}
	if (ft_strlen(argv[1]) < 3
	|| ft_strcmp(argv[1] + ft_strlen(argv[1]) - 2, ".s"))
	{
		ft_printf_fd(2, "You can only pass a '{cyan}.s{eoc}' file\n");
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_printf_fd(2, "{red}Failed{eoc} to open {bright}%s{eoc}\n", argv[1]);
		exit(1);
	}
	return (fd);
}

/*
** Function to create the corresponding .cor file name
*/

static char	*ft_get_new_file_name(t_asm_env *env, const char *input_name)
{
	char	*output_name;

	if (!(output_name = ft_strnew((ft_strlen(input_name) + 2) * sizeof(char))))
		ft_error(env, "Can't malloc", -1, -1);
	ft_strncpy(output_name, input_name, ft_strlen(input_name) - 1);
	ft_strcat(output_name, "cor");
	return (output_name);
}

int			main(int argc, char const *argv[])
{
	t_asm_env	asm_env;
	int			fd_output;
	char		*output_file_name;

	asm_env.fd_input = ft_open_file(argc, argv);
	asm_env.bin_buff = NULL;
	asm_env.bin_size = 0;
	asm_env.line_num = 0;
	asm_env.file_name = argv[1];
	asm_env.label_lst = NULL;
	ft_get_header(&asm_env);
	ft_parse(&asm_env);
	ft_put_addr(&asm_env);
	if (asm_env.bin_size == 0)
		ft_error(&asm_env, "The champion is empty!", -1, -1);
	output_file_name = ft_get_new_file_name(&asm_env, argv[1]);
	fd_output = open(output_file_name, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IWOTH);
	ft_write_output(&asm_env, fd_output, output_file_name);
	ft_strdel(&output_file_name);
	close(fd_output);
	ft_quit(&asm_env, 0);
	return (0);
}
