/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:49:54 by gkehren           #+#    #+#             */
/*   Updated: 2022/03/21 01:29:21 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nb(long nb)
{
	int	len;

	len = 1;
	if (nb < 0)
		nb = nb * -1;
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*ft_fillnbr(char *str, long nbr, int i)
{
	int	j;

	str[i] = '\0';
	i--;
	if (nbr < 0)
	{
		str[0] = '-';
		j = 1;
		nbr *= -1;
	}
	else
		j = 0;
	while (i >= j)
	{
		str[i] = 48 + (nbr % 10);
		nbr = nbr / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		i;

	nbr = n;
	i = len_nb(nbr);
	if (nbr < 0)
		i++;
	str = ft_strnew(i);
	if (!str)
		return (NULL);
	str = ft_fillnbr(str, nbr, i);
	return (str);
}
