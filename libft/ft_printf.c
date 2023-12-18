/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:46:51 by vilibert          #+#    #+#             */
/*   Updated: 2023/11/07 15:36:55 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_hex(unsigned long long n, char cap, int *length)
{
	int	status;

	if (n / 16)
	{
		status = print_hex(n / 16, cap, length);
		if (status == -1)
			return (-1);
	}
	if (n % 16 < 10 && ft_putchar((n % 16) + '0', length) == -1)
		return (-1);
	if (ft_putchar((n % 16) + (cap - 10), length) == -1)
		return (-1);
	return (1);
}

static int	format_handler(const char *format, va_list args, int *length)
{
	if (format[1] == 'c')
		return (ft_putchar((char)va_arg(args, int), length));
	if (format[1] == 's')
		return (ft_putstr(va_arg(args, char *), length));
	if (format[1] == 'p')
	{
		if (ft_putstr("0x", length) != 1)
			return (-1);
		return (print_hex(va_arg(args, unsigned long long), 'a', length));
	}
	if ((format[1] == 'd' || format[1] == 'i'))
		return (ft_putnbr(va_arg(args, int), length));
	if (format[1] == 'u')
		return (ft_putunbr(va_arg(args, unsigned int), length) == -1);
	if (format[1] == 'x')
		return (print_hex(va_arg(args, unsigned int), 'a', length));
	if (format[1] == 'X')
		return (print_hex(va_arg(args, unsigned int), 'A', length));
	else
		return (ft_putchar(format[1], length));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		length;

	va_start(args, format);
	i = 0;
	length = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format_handler(&format[i], args, &length) == -1)
				return (-1);
			i++;
		}
		else if (format[i] != '%')
		{
			if (ft_putchar(format[i], &length) == -1)
				return (-1);
		}
		i++;
	}
	va_end(args);
	return (length);
}
