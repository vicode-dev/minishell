/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:21:55 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 19:08:08 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	cd_export(t_data *data, char **url, char *s1, char *s2)
{
	free(url[1]);
	url[1] = ft_strjoin(s1, s2);
	free(s2);
	if (!url[1])
		return (1);
	ft_export(data, url);
	return (0);
}

void	ft_cd(t_data *data, char **argv)
{
	char	*oldtmp;
	char	*url[3];

	url[2] = 0;
	data->status = 1;
	if (!argv[1])
		url[1] = go_home(data);
	else
		url[1] = check_relative(data, argv[1]);
	if (!url[1])
		return ;
	oldtmp = getcwd(NULL, 0);
	if (chdir(url[1]) == -1)
	{
		ft_printf(2, "minishell: cd: %s: %s\n", url[1], strerror(errno));
		free(url[1]);
		free(oldtmp);
		return ;
	}
	if (cd_export(data, url, "OLDPWD=", oldtmp))
		return ;
	if (cd_export(data, url, "PWD=", getcwd(NULL, 0)))
		return ;
	data->status = 0;
}
