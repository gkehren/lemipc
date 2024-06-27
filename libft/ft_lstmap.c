/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:10:31 by gkehren           #+#    #+#             */
/*   Updated: 2022/04/08 01:13:42 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*new;

	elem = 0;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			while (elem)
			{
				new = elem->next;
				(*del)(elem->content);
				free(elem);
				elem = new;
			}
			lst = 0;
			return (0);
		}
		ft_lstadd_back(&elem, new);
		lst = lst->next;
	}
	return (elem);
}
