/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:01:23 by jgoudema          #+#    #+#             */
/*   Updated: 2023/12/18 20:44:30 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_temp.h"

int	ft_cd(t_data *data, char *dir_path)
{
	int	pwd;
	int	old;

	pwd = 0;
	while (ft_strncmp(data->env[pwd].name, "PWD", 3) != 0)
		pwd++;
	old = pwd + 1;
	free(data->env[old].content);
	data->env[old].content = data->env[pwd].content;
	data->env[pwd].content = ft_strdup(dir_path);
	return (0);
}
