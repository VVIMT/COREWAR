/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 02:52:54 by fmuller           #+#    #+#             */
/*   Updated: 2017/11/17 01:06:54 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		ft_is_flags(char c)
{
	return ((c == '-' || c == '+' || c == ' ' || c == '0' || c == '#' ||
		c == '\''));
}

int		ft_is_type(char c)
{
	return (c == 'd' || c == 'D' || c == 'i' || c == 'u' || c == 'U' ||
		c == 'f' || c == 'F' || c == 'e' || c == 'E' || c == 'g' || c == 'G'
		|| c == 'x' || c == 'X' || c == 'o' || c == 'O' || c == 's' || c == 'S'
		|| c == 'c' || c == 'C' || c == 'p' || c == 'a' || c == 'A' || c == 'n'
		|| c == '%' || c == 'b' || c == 'B');
}

int		ft_is_nbr(char c)
{
	return (c == 'd' || c == 'D' || c == 'i' || c == 'u' || c == 'U'
		|| c == 'x' || c == 'X' || c == 'o' || c == 'O' || c == 'b'
		|| c == 'B');
}

int		ft_is_lenght(char c)
{
	return (c == 'h' || c == 'l' || c == 'L' || c == 'z' || c == 'j');
}
