/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 22:59:09 by foasman           #+#    #+#             */
/*   Updated: 2026/11/10 23:16:03 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(const char *str)
{
	int	i;

	if (!str)
		return (ft_print_str("(null)"));
	i = 0;
	while (str[i])
	{
		if (ft_print_char(str[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}
