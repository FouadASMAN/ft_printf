/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:30:23 by foasman           #+#    #+#             */
/*   Updated: 2026/11/11 17:36:36 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int ui)
{
	char	wallet[13];
	int		i;
	int		count;

	if (ui == 0)
		return (ft_print_char('0'));
	i = 0;
	while (ui > 0)
	{
		wallet[i] = ui % 10 + '0';
		ui = ui / 10;
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
