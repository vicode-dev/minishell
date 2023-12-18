/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:08:42 by jgoudema          #+#    #+#             */
/*   Updated: 2023/12/18 21:12:25 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_data *data)
{
	int		i;
	char	*pwd;

	i = 0;
	while (ft_strncmp(data->env[i], "PWD", 3) != 0)
		i++;
	pwd = data->env[i];
	pwd += 4;
	ft_printf("%s\n", pwd);
	return (0);
}
