/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:34:50 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/08 19:12:10 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data *data, int out)
{
	int	i;

	i = 0;
	while (data->env[i])
		ft_printf(out, "%s\n", data->env[i++]);
	return (0);
}
