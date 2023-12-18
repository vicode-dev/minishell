/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:01:41 by jgoudema          #+#    #+#             */
/*   Updated: 2023/12/18 21:15:06 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_temp.h"

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i].name)
	{
		ft_printf("%s=%s\n", data->env[i].name, data->env[i].content);
		i++;
	}
	return (0);
}
