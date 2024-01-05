/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:33:22 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 17:16:51 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_printf(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_printf(char *s)
{
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
		count += write(1, s++, 1);
	return (count);
}
