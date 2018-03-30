/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 00:01:47 by fmuller           #+#    #+#             */
/*   Updated: 2018/02/23 00:51:01 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_aff(t_cor_env *cor_env, t_process *process, int index)
{
	char	c;

	c = ft_get_full_param_value(cor_env, process, first, index) % 256;
	ft_printf("{green}%c{eoc}", c);
}
