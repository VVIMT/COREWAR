/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 19:51:43 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/22 22:46:59 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"

# define BIN_BUFF_SIZE 420

typedef struct	s_label
{
	int				tab_size;
	char			*name;
	int				def_addr;
	unsigned int	*param_addr;
	int				*param_size;
	unsigned int	*inst_addr;
	struct s_label	*next;
}				t_label;

typedef struct	s_asm_env
{
	unsigned char	magic[MAGIC_LENGTH];
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned char	*bin_buff;
	unsigned int	bin_size;
	unsigned int	instruction_addr;
	int				line_num;
	int				fd_input;
	const char		*file_name;
	t_label			*label_lst;
}				t_asm_env;

int				ft_asm_gnl(t_asm_env *asm_env, const int fd, char **line);
int				ft_pass_space(t_asm_env *asm_env, char **str);
void			ft_check_bin_buff(t_asm_env *env, unsigned int size);
void			ft_write_nb(t_asm_env *env, int nbr, int len);
void			ft_write_nb_addr(t_asm_env *env, int nbr, int len,
															unsigned int addr);
void			ft_check_endline(t_asm_env *asm_env, char *line, int end);

void			ft_get_header(t_asm_env *asm_env);
void			ft_get_string(t_asm_env *asm_env, char **line, int i,
																	int *type);

void			ft_parse(t_asm_env	*asm_env);
int				ft_is_instruction(char *line);
void			ft_instruction_line(t_asm_env *env, char *line, int i,
																int inst_num);
t_arg_type		ft_param_type(t_asm_env *env, char *line, int i);
void			ft_label_line(t_asm_env *env, char *line, int i);
void			ft_add_label_dest(t_asm_env *env, char *line, int size);

void			ft_write_output(t_asm_env *asm_env, int fd_output,
														char *output_file_name);

void			ft_error(t_asm_env *asm_env, char *message, int line, int col);
void			ft_quit(t_asm_env *asm_env, int ret_value);

#endif
