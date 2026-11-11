/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_select.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 17:27:11 by foasman           #+#    #+#             */
/*   Updated: 2026/11/10 23:30:44 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_select(char ch, va_list *ap)
{
	if (ch == 'c')
		return (ft_print_char(va_arg(*ap, int)));
	else if (ch == 'd' || ch == 'i')
		return (ft_print_nbr(va_arg(*ap, int)));
	else if (ch == 'u')
		return (ft_print_unsigned(va_arg(*ap, unsigned int)));
	else if (ch == 'x' || ch == 'X')
	{
		if (ch == 'x')
			return (ft_print_hex(va_arg(*ap, unsigned int),
					"0123456789abcdef"));
		else
			return (ft_print_hex(va_arg(*ap, unsigned int),
					"0123456789ABCDEF"));
	}
	else if (ch == 's')
		return (ft_print_str(va_arg(*ap, char *)));
	else if (ch == 'p')
		return (ft_print_ptr(va_arg(*ap, void *)));
	return (-1);
}
