/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:21:55 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/09 09:50:37 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>

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

char	*check_relative(t_data *data, char *path_dir)
{
	char	*tmp;

	if (!ft_strncmp(path_dir, "~", 1))
	{
		tmp = ft_strjoin(get_env_var(data->env, "HOME"), ++path_dir);
		free(--path_dir);
		return (tmp);
	}
	if (!ft_strncmp(path_dir, "-", 2))
	{
		if (!get_env_var(data->env, "OLDPWD"))
			return (ft_printf(2, "minishell: cd: OLDPWD not set\n"), NULL);
		tmp = ft_strdup(get_env_var(data->env, "OLDPWD"));
		if (access(tmp, R_OK | F_OK))
			ft_printf(1, "%s\n", tmp);
		return (free(path_dir), tmp);
	}
	return (path_dir);
}

int	ft_cd(t_data *data, char *path_dir)
{
	char *oldtmp;

	oldtmp = getcwd(NULL, 0);
	path_dir = check_relative(data, path_dir);
	if(!oldtmp || chdir(path_dir) == -1)
	{
		// PUT CONDITION HERE
		ft_printf(2, "cd: %s : %s\n", strerror(errno), path_dir);
		return (free(path_dir), free(oldtmp), 1);
	}


	int i;
	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "OLDPWD", 6) != 0)
		i++;
	if (data->env[i])
	{
		free(data->env[i]);
		data->env[i] = ft_strjoin("OLDPWD=", oldtmp);
	}
	// else
	// {
	// 	ft_export(ft_strjoin("OLDPWD=", oldtmp)); //????
	// }
	free(oldtmp);
	oldtmp = getcwd(NULL, 0);
	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "PWD", 3) != 0)
		i++;
	if (data->env[i])
	{
		free(data->env[i]);
		data->env[i] = ft_strjoin("PWD=", oldtmp);
	}
	// else
	// {
	// 	ft_export(ft_strjoin("PWD=", oldtmp)); //????
	// }
	free(oldtmp);

	// parse_path(data, path_dir);
	// change_env(data, path_dir);
	// chdir(path_dir);
	// data->env[pwd];
	
	return (0);
}
