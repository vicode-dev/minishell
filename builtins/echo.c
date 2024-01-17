/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:39:02 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/17 20:34:58 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	echo_flag(char *arg)
// {
// 	int	j;
// 	int	flag;

// 	j = 0;
// 	flag = 0;
// 	if (!arg)
// 		return (-1);
// 	while (arg[j])
// 	{
// 		while (arg[j] == ' ')
// 			j++;
// 		if (arg[j++] == '-')
// 			while (arg[j] == 'n')
// 				j++;
// 		if (arg[j] != ' ' && arg[j] != 0)
// 			break ;
// 		while (arg[j] == ' ')
// 			j++;
// 		flag = j;
// 	}
// 	return (flag);
// }

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

int	ft_echo(char **argv)
{
	int	flag;
	int	j;

	// (void) data;
	// flag = echo_flag(args[1]);
	// i = flag;
	// while (args[1] && args[1][i])
	// 	ft_printf(out, "%c", args[1][i++]);
	// if (flag <= 0)
	// 	ft_printf(out, "\n");
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
	return (0);
}
