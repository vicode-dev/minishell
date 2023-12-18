/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:12:12 by vilibert          #+#    #+#             */
/*   Updated: 2023/11/20 16:40:25 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c, int *length)
{
	int	status;

	status = write(1, &c, 1);
	if (status == 1)
		*(length) += 1;
	return (status);
}

int	ft_putstr(char *str, int *length)
{
	int	status;

	if (str == NULL)
		return (ft_putstr("(null)", length));
	while (*str)
	{
		status = ft_putchar(*str++, length);
		if (status != 1)
			return (status);
	}
	return (status);
}

int	ft_putnbr(int n, int *length)
{
	char	*nbr;
	int		status;

	nbr = ft_itoa(n);
	status = ft_putstr(nbr, length);
	free(nbr);
	return (status);
}

int	ft_putunbr(unsigned int n, int *length)
{
	char	*nbr;
	int		status;

	nbr = ft_uitoa(n);
	status = ft_putstr(nbr, length);
	free(nbr);
	return (status);
}
