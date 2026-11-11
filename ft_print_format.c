/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 15:22:13 by foasman           #+#    #+#             */
/*   Updated: 2026/11/10 17:19:25 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_conversion(const char *format, int i, va_list *ap)
{
	if (format[i + 1] == '%')
	{
		if (ft_print_char('%') <= 0)
			return (-1);
		return (1);
	}
	else if (format[i + 1])
		return (ft_print_select(format[i + 1], ap));
	return (-1);
}

int	ft_print_format(const char *format, va_list *ap)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			if (ft_print_char(format[i]) <= 0)
				return (-1);
			count++;
		}
		else
		{
			check = ft_print_conversion(format, i, ap);
			if (check == -1)
				return (-1);
			count += check;
			i++;
		}
		i++;
	}
	return (count);
}
