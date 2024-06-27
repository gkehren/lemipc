/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:25:59 by gkehren           #+#    #+#             */
/*   Updated: 2022/03/13 16:33:05 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	ptr = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			ptr = (char *)haystack + i;
			j = 0;
			while (haystack[i + j] == needle[j])
			{
				if (needle[j + 1] == '\0')
					return (ptr);
				j++;
			}
			ptr = 0;
		}
		i++;
	}
	return (0);
}
