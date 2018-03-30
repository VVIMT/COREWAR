/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:29:01 by fmuller           #+#    #+#             */
/*   Updated: 2017/11/17 00:07:37 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Version 3.0: sans malloc
*/

char	*ft_str_insert(char **dst, char *src, size_t index, size_t dst_len)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	ft_memmove(*dst + index + src_len, *dst + index, dst_len - index);
	ft_memcpy(*dst + index, src, src_len);
	return (*dst);
}
