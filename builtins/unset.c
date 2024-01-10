/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:15:55 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/10 15:30:56 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_name(char *name)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (!ft_isalnum(name[j]) && name[j] != '_')
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", name);
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_unset(t_data *data, *arg)
{
	int	exit;

	exit = check_name(arg, 1);
	return (0);
}
