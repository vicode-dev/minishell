/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:54:41 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/17 20:40:00 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int g_exitcode;

void	ft_exit(t_data *data, char **argv)
{
	// int64 -> max possible sinon erreur 9223372036854775807
	if (argv[1] && argv[2])
	{
		data->status = 1;
		ft_printf(2, "exit: too many arguments\n");
	}
	else if (argv[1])
	{
		data->status = ft_atoi(argv[1]);
		g_exitcode = ft_atoi(argv[1]);
		// if (argv[1] > INT64_MAX) // passer argv[1] en int64
		// {
		// 	ft_printf(2, "exit: %s: numeric argument required\n", argv[1]);
		// 	data->status = 255;
		// }
	}
	ft_exit_prog(data);
}
