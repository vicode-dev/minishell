/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:34:50 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/18 17:28:22 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')
			j++;
		if (data->env[i][j] == '=')
			ft_printf(1, "%s\n", data->env[i]);
		i++;
	}
	data->status = 0;
}
