/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 23:52:08 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/22 22:43:59 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		end_tab(char tab[7])
{
	tab[0] = LABEL_CHAR;
	tab[1] = 0;
	tab[2] = ' ';
	tab[3] = '\t';
	tab[4] = '\v';
	tab[5] = '\f';
	tab[6] = '\r';
	tab[7] = SEPARATOR_CHAR;
	tab[8] = COMMENT_CHAR;
	tab[9] = 0;
}

t_label		*already_created(t_asm_env *env, char *line, int flag)
{
	char	tab[10];
	t_label	*tmp;
	size_t	len;

	end_tab(tab);
	tmp = env->label_lst;
	len = ft_strlen_c(line, (flag == 0 ? tab : tab + 2));
	while (tmp)
	{
		if (ft_strlen(tmp->name) == len && !ft_strncmp(tmp->name, line, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_label		*ft_create_label(t_asm_env *env, char *line, int flag)
{
	char	tab[10];
	char	*name;
	t_label	*new;

	end_tab(tab);
	if (!(new = ft_memalloc(sizeof(t_label))))
		ft_error(env, "Allocation failure", -1, -1);
	new->next = env->label_lst;
	env->label_lst = new;
	if (!(name = ft_memalloc(
						ft_strlen_c(line, (flag == 0 ? tab : tab + 2)) + 1)))
		ft_error(env, "Allocation failure", -1, -1);
	env->label_lst->name = name;
	ft_strcpy_c(name, line, (flag == 0 ? tab : tab + 2));
	env->label_lst->param_addr = NULL;
	env->label_lst->param_size = NULL;
	env->label_lst->tab_size = 0;
	env->label_lst->def_addr = -1;
	return (env->label_lst);
}

void		ft_label_line(t_asm_env *env, char *line, int i)
{
	t_label	*lst;
	char	tab[10];
	int		n;

	lst = already_created(env, line + i, 0);
	if (!lst)
		lst = ft_create_label(env, line + i, 0);
	if (lst->def_addr == -1)
		lst->def_addr = env->bin_size;
	end_tab(tab);
	i = ft_strlen_c(line + i, tab) + 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if ((n = ft_is_instruction(line + i)) != -1)
		ft_instruction_line(env, line, i + ft_strlen(g_op_tab[n].name), n);
	else if (line[i] && line[i] != '#')
		ft_error(env, "Unexpected character", env->line_num, i + 1);
}

void		ft_add_label_dest(t_asm_env *env, char *line, int size)
{
	t_label			*lst;
	unsigned int	*p_addr;
	unsigned int	*i_addr;
	int				*p_size;

	lst = already_created(env, line, 1);
	if (!lst)
		lst = ft_create_label(env, line, 1);
	p_addr = lst->param_addr;
	p_size = lst->param_size;
	i_addr = lst->inst_addr;
	if (!(p_addr = realloc(p_addr, (lst->tab_size + 1) * sizeof(int)))
	|| (!(p_size = realloc(p_size, (lst->tab_size + 1) * sizeof(int))))
	|| (!(i_addr = realloc(i_addr, (lst->tab_size + 1) * sizeof(int)))))
		ft_error(env, "Error with realloc", -1, -1);
	lst->param_addr = p_addr;
	lst->param_size = p_size;
	lst->inst_addr = i_addr;
	lst->param_addr[lst->tab_size] = env->bin_size;
	lst->param_size[lst->tab_size] = size;
	lst->inst_addr[lst->tab_size] = env->instruction_addr;
	ft_write_nb(env, 0, size);
	++(lst->tab_size);
}
