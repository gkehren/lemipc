/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:24:51 by gkehren           #+#    #+#             */
/*   Updated: 2022/03/18 16:38:47 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*memalloc;

	memalloc = malloc(size);
	if (!memalloc)
		return (NULL);
	else
		ft_bzero(memalloc, size);
	return (memalloc);
}
