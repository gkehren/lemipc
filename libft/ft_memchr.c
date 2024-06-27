/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:17:07 by gkehren           #+#    #+#             */
/*   Updated: 2022/03/13 22:24:34 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)s;
	while (i < (int)n)
	{
		if (temp[i] == (char)c)
			return ((void *)temp + i);
		i++;
	}
	return (NULL);
}
