/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:21:55 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/18 21:13:52 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_env(t_data *data, char *path_dir)
{
	int	pwd;
	int old_pwd;
	char *temp;
	char *temp_temp;

	pwd = 0;
	old_pwd = 0;
	while (ft_strncmp(data->env[pwd], "PWD", 3))
		pwd++;
	while (ft_strncmp(data->env[old_pwd], "OLDPWD", 6))
		old_pwd++;
	temp = ft_strdup(path_dir);
	if (!temp)
		return (1);
	temp_temp = ft_strjoin("PWD=", temp);
	free(temp);
	free(data->env[old_pwd]);
	data->env[old_pwd] = ft_strjoin("OLD", data->env[pwd]);
	free(data->env[pwd]);
	data->env[pwd] = temp_temp;
	return (0);
}
// int	parse_path(t_data *data, char *path_dir)
// {
// 	if (path_dir[0] != '/')
// 	{
		
// 	}
// }

int	ft_cd(t_data *data, char *path_dir)
{
	int 	pwd;

	pwd = 0;
	while (ft_strncmp(data->env[pwd], "PWD", 3))
		pwd++;
	if (access(path_dir, F_OK | R_OK) == 0)
	{
		ft_printf("try to change\n");
		// parse_path(data, path_dir);
		// change_env(data, path_dir);
		chdir(path_dir);
		// data->env[pwd];
	}
	return (0);
}
