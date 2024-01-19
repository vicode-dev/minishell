/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:21:55 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/19 16:33:45 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>

// int	change_env(t_data *data, char *path_dir)
// {
// 	int	pwd;
// 	int old_pwd;
// 	char *temp;
// 	char *temp_temp;

// 	pwd = 0;
// 	old_pwd = 0;
// 	while (ft_strncmp(data->env[pwd], "PWD", 3))
// 		pwd++;
// 	while (ft_strncmp(data->env[old_pwd], "OLDPWD", 6))
// 		old_pwd++;
// 	temp = ft_strdup(path_dir);
// 	if (!temp)
// 		return (1);
// 	temp_temp = ft_strjoin("PWD=", temp);
// 	free(temp);
// 	free(data->env[old_pwd]);
// 	data->env[old_pwd] = ft_strjoin("OLD", data->env[pwd]);
// 	free(data->env[pwd]);
// 	data->env[pwd] = temp_temp;
// 	return (0);
// }
// int	parse_path(t_data *data, char *path_dir)
// {
// 	if (path_dir[0] != '/')
// 	{
		
// 	}
// }

char	*check_relative(t_data *data, char *path_dir)
{
	char	*tmp;


	if (!ft_strncmp(path_dir, "-", 2))
	{
		if (!get_env_var(data->env, "OLDPWD"))
			return (ft_printf(2, "minishell: cd: OLDPWD not set\n"), NULL);
		tmp = ft_strdup(get_env_var(data->env, "OLDPWD"));
		if (!access(tmp, R_OK | F_OK))
			ft_printf(1, "%s\n", tmp);
		return (tmp);
	}
	return (ft_strdup(path_dir));
}
char	*go_home(t_data *data)
{
	char	*home;

	home = get_env_var(data->env, "HOME");
	if (!home)
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		return (NULL);
	}
	return (ft_strdup(home));
}

void	ft_cd(t_data *data, char **argv)
{
	char 	*oldtmp;
	char	*url[3];

	url[2] = 0;
	if (!argv[1])
		url[1] = go_home(data);
	else
		url[1] = check_relative(data, argv[1]);
	if (!url[1])
	{
		data->status = 1;
		return ;
	}
	oldtmp = getcwd(NULL, 0);
	if (chdir(url[1]) == -1)
	{
		ft_printf(2, "cd: %s : %s\n", strerror(errno), url[1]);
		free(url[1]);
		free(oldtmp);
		data->status = 1;
		return ;
	}
	free(url[1]);
	url[1] = ft_strjoin("OLDPWD=", oldtmp);
	free(oldtmp);
	if (!url[1])
	{
		data->status = 1;
		return ;
	}
	ft_export(data, url);
	free(url[1]);
	url[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!url[1])
	{
		data->status = 1;
		return ;
	}
	ft_export(data, url);
	free(url[1]);
	data->status = 0;
}
