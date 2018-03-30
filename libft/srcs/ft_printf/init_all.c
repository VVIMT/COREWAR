/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:46:22 by fmuller           #+#    #+#             */
/*   Updated: 2017/11/17 01:06:57 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_reset_all_printf(t_all *all)
{
	all->output = ft_strnew(all->len);
	all->i = 0;
	all->current_param = 1;
	all->end = 0;
	all->write = 1;
	all->rett = 0;
	all->len = 0;
	all->color_status = ft_init_status();
	return (all->output);
}

void	ft_init_all_printf(t_all *all)
{
	all->output = NULL;
	all->param_list = NULL;
	all->i = 0;
	all->current_param = 1;
	all->end = 0;
	all->write = 0;
	all->rett = 0;
	all->len = 0;
	all->color_status = ft_init_status();
}
