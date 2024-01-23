/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:54:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/19 17:27:19 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdint.h>

static int	exit_error_print(const char *str)
{
	ft_printf(2, "minishell: exit: %s: numeric argument required\n", str);
	return (-1);
}

static int64_t	ft_atoi64(const char *str)
{
	int64_t	res;
	int64_t	last;
	int		neg;
	int		i;

	res = 0;
	neg = 1;
	last = 0;
	i = 0;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res == INT64_MAX / 10 && str[i] == '8' && neg == -1)
			return (INT64_MIN);
		res = res * 10 + (str[i] - 48);
		if (last > res)
			return (exit_error_print(str));
		i++;
		last = res;
	}
	return (res * neg);
}

static int	exit_check_arg(char *str)
{
	int	i;
	int	num_len;

	i = 0;
	num_len = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (num_len > 18 && str[i])
			return (0);
		i++;
		num_len++;
	}
	return (1);
}

void	ft_exit(t_data *data, char **argv)
{
	int64_t	code;

	if (argv[1] && !exit_check_arg(argv[1]))
		data->status = exit_error_print(argv[1]);
	else if (argv[1] && argv[2])
	{
		data->status = 1;
		ft_printf(2, "minishell: exit: too many arguments\n");
		return ;
	}
	else if (argv[1])
	{
		code = ft_atoi64(argv[1]);
		data->status = code;
	}
	ft_exit_prog(data);
}
