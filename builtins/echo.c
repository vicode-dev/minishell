/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:02 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/11 19:50:37 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_flag(char *arg)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	if (!arg)
		return (-1);
	while (arg[j])
	{
		while (arg[j] == ' ')
			j++;
		if (arg[j++] == '-')
			while (arg[j] == 'n')
				j++;
		if (arg[j] != ' ' && arg[j] != 0)
			break ;
		while (arg[j] == ' ')
			j++;
		flag = j;
	}
	return (flag);
}

int	ft_echo(t_data *data, char **args, int out)
{
	int	flag;
	int	i;

	(void) data;
	flag = echo_flag(args[1]);
	i = flag;
	while (args[1] && args[1][i])
		ft_printf(out, "%c", args[1][i++]);
	if (flag <= 0)
		ft_printf(out, "\n");
	return (0);
}
