/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 23:43:17 by foasman           #+#    #+#             */
/*   Updated: 2026/11/11 15:52:45 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(const void *ptr)
{
	int	check1;
	int	check2;

	if (!ptr)
		return (ft_print_str("(nil)"));
	check1 = ft_print_str("0x");
	if (check1 == -1)
		return (-1);
	check2 = ft_print_hex((unsigned long)ptr, "0123456789abcdef");
	if (check2 == -1)
		return (-1);
	return (check1 + check2);
}
