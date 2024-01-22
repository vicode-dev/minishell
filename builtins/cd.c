/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:21:55 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/22 18:01:51 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>

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
	char	*oldtmp;
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
