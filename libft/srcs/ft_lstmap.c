/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:11:53 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/20 19:10:23 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*tmp_list;

	if (!(new_list = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	tmp_list = new_list;
	if (!lst)
		return (NULL);
	while (lst)
	{
		tmp_list->next = (*f)(lst);
		lst = lst->next;
		tmp_list = tmp_list->next;
	}
	return (new_list->next);
}
