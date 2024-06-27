/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:01:13 by gkehren           #+#    #+#             */
/*   Updated: 2022/04/08 01:11:38 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*elem;

	if (lst && del)
	{
		while (lst && *lst)
		{
			elem = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = elem;
		}
	}
}
