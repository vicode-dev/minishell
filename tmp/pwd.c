/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:04:00 by jgoudema          #+#    #+#             */
/*   Updated: 2023/12/18 21:17:21 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_temp.h"

int	ft_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (ft_strncmp(data->env[i].name, "PWD", 3) != 0)
		i++;
	ft_printf("%s\n", data->env[i].content);
	return (0);
}
