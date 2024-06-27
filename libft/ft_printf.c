/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:07:09 by gkehren           #+#    #+#             */
/*   Updated: 2022/05/09 14:18:28 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(char c)
{
	int	len;

	len = 0;
	len += write(1, &c, 1);
	return (len);
}

int	ft_print_str(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
	{
		len += write(1, "(null)", 6);
		return (len);
	}
	while (str[i] != '\0')
		len += write(1, &str[i++], 1);
	return (len);
}

int	ft_return_addr(unsigned long n, char *hex)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += ft_return_addr(n / 16, hex);
	i += write(1, hex + (n % 16), 1);
	return (i);
}

int	ft_addr(unsigned long n)
{
	int	i;

	if (n == 0)
		i = ft_print_str("(nil)");
	else
	{
		i = ft_print_str("0x");
		i += ft_return_addr(n, "0123456789abcdef");
	}
	return (i);
}

int	ft_print_nbr_base(unsigned int n, char *base)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += ft_print_nbr_base(n / 16, base);
	len += write(1, (base + (n % 16)), 1);
	return (len);
}

int	ft_print_nbr(int nb)
{
	long	i;
	int		len;

	len = 0;
	i = nb;
	if (i < 0)
	{
		len = ft_print_char('-');
		i *= -1;
	}
	if (i > 9)
	{
		len += ft_print_nbr(i / 10);
		len += ft_print_nbr(i % 10);
	}
	else
		len += ft_print_char(i + '0');
	return (len);
}

int	ft_print_nbr_u(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n > 9)
		ret += ft_print_nbr_u(n / 10);
	ret += ft_print_char((n % 10) + '0');
	return (ret);
}

int	ft_print_arg(va_list params, char c)
{
	int		len;

	len = 0;
	if (c == '%')
		len += ft_print_char('%');
	if (c == 's')
		len += ft_print_str((char *)va_arg(params, char *));
	if (c == 'c')
		len += ft_print_char(va_arg(params, int));
	if (c == 'p')
		len += ft_addr((unsigned long)va_arg(params, void *));
	if (c == 'd')
		len += ft_print_nbr(va_arg(params, int));
	if (c == 'i')
		len += ft_print_nbr(va_arg(params, int));
	if (c == 'u')
		len += ft_print_nbr_u(va_arg(params, int));
	if (c == 'x')
		len += ft_print_nbr_base(va_arg(params, int), "0123456789abcdef");
	if (c == 'X')
		len += ft_print_nbr_base(va_arg(params, int), "0123456789ABCDEF");
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	params;

	i = 0;
	len = 0;
	va_start(params, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			len += ft_print_arg(params, str[i + 1]);
			i++;
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(params);
	return (len);
}
