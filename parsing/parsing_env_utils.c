/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:25:51 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/17 17:25:43 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_strs(char **board, int i, int quit)
{
	while (board && board[i])  // while (i >= 0) et decrementer
		free(board[i++]);
	free(board);
	if (quit == 1 || quit == 0)
		exit(quit);
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
	char		*old_value;
	char		*itoa;
	uint16_t	shlvl;
	int			i;

	i = 0;
	old_value = get_env_var(data->env, "SHLVL");
	if (old_value)
		shlvl = ft_atoi(old_value);
	else
		shlvl = -1;
	shlvl++;
	while (data->env[i]
		&& ft_strncmp(data->env[i], "SHLVL=", ft_strlen("SHLVL=")))
		i++;
	free(data->env[i]);
	itoa = ft_itoa(shlvl);
	data->env[i] = ft_strjoin("SHLVL=", itoa);
	free(itoa);
	if (!data->env[i])
		ft_crash(data);
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
	// data->var = malloc(sizeof(char *));
	// if (!data->var)
	// 	ft_free_strs(data->env, i, 1);
	// data->var[0] = NULL;
	increase_shlvl(data);
}
