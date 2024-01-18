/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:54:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/18 16:35:02 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdint.h>

int64_t	ft_atoi64(const char *str)
{
	int64_t	res;
	int64_t	last;
	int		neg;

	res = 0;
	neg = 1;
	last = 0;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (res == INT64_MAX / 10 && *str == '8' && neg == -1)
			return (INT64_MIN);
		res = res * 10 + (*str - 48);
		if (last > res)
			ft_printf(2, "exit: %s: numeric argument required\n", str);
		if (last > res)
			return (255);
		str++;
		last = res;
	}
	return (res * neg);
}

int	exit_check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (i > 19)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data, char **argv)
{
	int64_t	code;

	if (argv[1] && argv[2])
	{
		data->status = 1;
		ft_printf(2, "exit: too many arguments\n");
	}
	else if (argv[1] && !exit_check_arg(argv[1]))
	{
		ft_printf(2, "exit: %s: numeric argument required\n", argv[1]);
		data->status = 255;
	}
	else if (argv[1])
	{
		code = ft_atoi64(argv[1]);
		data->status = code;
	}
	ft_exit_prog(data);
}
