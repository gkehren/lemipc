/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:25:20 by gkehren           #+#    #+#             */
/*   Updated: 2022/05/10 20:46:25 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*c;
	unsigned char	*p;

	c = (unsigned char *)src;
	p = (unsigned char *)dst;
	while (n > 0)
	{
		*p = *c;
		p++;
		c++;
		n--;
	}
	return (dst);
}
