/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:53:32 by foasman           #+#    #+#             */
/*   Updated: 2026/11/11 17:53:03 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned long n, const char *base)
{
	char	wallet[19];
	int		i;
	int		count;

	if (n == 0)
		return (ft_print_char('0'));
	i = 0;
	while (n > 0)
	{
		wallet[i] = base[n % 16];
		n = n / 16;
		i++;
	}
	count = i;
	i--;
	while (i >= 0)
	{
		if (ft_print_char(wallet[i]) == -1)
			return (-1);
		i--;
	}
	return (count);
}
