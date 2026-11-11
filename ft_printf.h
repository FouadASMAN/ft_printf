/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foasman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:15:20 by foasman           #+#    #+#             */
/*   Updated: 2026/11/10 23:40:35 by foasman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_print_format(const char *format, va_list *ap);
int	ft_print_select(char ch, va_list *ap);
int	ft_print_char(char ch);
int	ft_print_str(const char *str);
int	ft_print_unsigned(unsigned int ui);
int	ft_print_hex(unsigned long n, const char *base);
int	ft_print_ptr(const void *ptr);
int	ft_print_nbr(int nb);

#endif
