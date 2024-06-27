/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 22:36:19 by gkehren           #+#    #+#             */
/*   Updated: 2022/03/11 23:34:00 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*car;

	i = 0;
	car = (char *)s;
	while (i < (int)n)
	{
		car[i] = (char)c;
		i++;
	}
	s = (void *)car;
	return (s);
}
