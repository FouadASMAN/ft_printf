/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:40:19 by foasman           #+#    #+#             */
/*   Updated: 2026/11/11 17:28:46 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_positive(long n)
{
	char	wallet[13];
	int		i;
	int		count;

	i = 0;
	while (n > 0)
	{
		wallet[i] = n % 10 + '0';
		n = n / 10;
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

int	ft_print_nbr(int nb)
{
	long	n;
	int		neg;
	int		count;

	n = nb;
	neg = 0;
	if (n == 0)
		return (ft_print_char('0'));
	if (n < 0)
	{
		n = -n;
		neg = ft_print_char('-');
		if (neg == -1)
			return (-1);
	}
	count = ft_print_positive(n);
	if (count == -1)
		return (-1);
	return (neg + count);
}
