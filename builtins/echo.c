/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:02 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/23 18:49:32 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_flag(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (-1);
	while (arg[i] == ' ')
		i++;
	if (arg[i++] == '-')
	{
		while (arg[i] == 'n')
			i++;
		if (arg[i] != ' ' && arg[i] != 0)
			return (0);
		return (1);
	}
	return (0);
}

static void	echo_print(char **argv, int j, int flag)
{
	if (argv[j])
		ft_printf(1, "%s", argv[j++]);
	while (argv[j])
		ft_printf(1, " %s", argv[j++]);
	if (!flag)
		ft_printf(1, "\n");
}

void	ft_echo(t_data *data, char **argv)
{
	int	flag;
	int	j;

	j = 1;
	flag = -1;
	while (argv[j])
	{
		if (flag == -1)
			flag = echo_flag(argv[j]);
		if (echo_flag(argv[j]) == 1)
			j++;
		else
			break ;
	}
	echo_print(argv, j, flag);
	data->status = 0;
}
