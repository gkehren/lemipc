/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:31:32 by gkehren           #+#    #+#             */
/*   Updated: 2022/03/18 17:42:55 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	int		j;

	i = (int)start;
	j = 0;
	str = ft_strnew(len + 1);
	if (!str)
		return (NULL);
	while (j < (int)len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
