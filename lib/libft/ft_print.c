/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:54:14 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 17:16:04 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checks(va_list va, char c)
{
	int	count;

	if (c == 'c')
		count = ft_putchar_printf(va_arg(va, int));
	else if (c == 's')
		count = (ft_putstr_printf(va_arg(va, char *)));
	else if (c == 'd' || c == 'i')
		count = (ft_sputnbr(va_arg(va, int)));
	else if (c == 'u')
		count = ft_uputnbr(va_arg(va, unsigned int), DEC);
	else if (c == 'x')
		count = ft_uputnbr(va_arg(va, unsigned int), HEXM);
	else if (c == 'X')
		count = ft_uputnbr(va_arg(va, unsigned int), HEXU);
	else if (c == 'p')
	{
		count = ft_putstr_printf("0x");
		count += ft_uputnbr((unsigned long)va_arg(va, void *), HEXM);
	}
	else if (c == '%')
		count = ft_putchar_printf('%');
	else
		count = write(1, &c, 1);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	va_list	va;

	len = 0;
	va_start(va, s);
	while (*s)
	{
		if (*s == '%')
			len += ft_checks(va, *(++s));
		else
			len += ft_putchar_printf(*s);
		s++;
	}
	va_end(va);
	return (len);
}
