/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:25:51 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/24 17:42:15 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tab_size(t_lexed *list)
{
	int	count;

	count = 1;
	while (list->next)
	{
		if (list->token == PIPE)
			count++;
		list = list->next;
	}
	return (count);
}

char	*get_env_var(char **env, char *var)
{
	int		i;
	char	*res;

	i = 0;
	if (!var || !var[0])
		return (NULL);
	while ((env[i] && ft_strncmp(env[i], var, ft_strlen(var))) 
		|| (env[i] && env[i][ft_strlen(var)] != '='))
		i++;
	if (env[i])
	{
		res = ft_strchr(env[i], '=');
		res++;
		return (res);
	}
	return (NULL);
}

void	increase_shlvl(t_data *data)
{
	char		*itoa;
	char		*new_line[3];
	int64_t		shlvl;

	shlvl = 1;
	if (get_env_var(data->env, "SHLVL"))
		shlvl += ft_atoi64(get_env_var(data->env, "SHLVL"));
	if (shlvl <= 0)
		shlvl = 0;
	if (shlvl > 1000)
		shlvl = 1;
	itoa = ft_itoa(shlvl);
	new_line[1] = ft_strjoin("SHLVL=", itoa);
	if (shlvl == 1000)
	{
		free(new_line[1]);
		new_line[1] = ft_strdup("SHLVL=");
	}
	new_line[2] = 0;
	if (!new_line[1])
		ft_crash(data);
	free(itoa);
	ft_export(data, new_line);
	free(new_line[1]);
	data->status = 0;
}

void	get_env(char **env, t_data *data)
{
	char	**new;
	int		i;

	new = malloc((ft_strslen(env) + 1) * sizeof(char *));
	if (!new)
		exit (1);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			ft_free_strs(new, i, 1);
		i++;
	}
	new[i] = NULL;
	data->env = new;
	increase_shlvl(data);
}
