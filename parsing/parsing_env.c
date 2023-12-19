/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:25:51 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/19 17:02:23 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

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
	// char	*tmp;

	// tmp = ft_strjoin(var, "=");
	// var = tmp;
	i = 0;

	while (env[i] && ft_strncmp(env[i], var, ft_strlen(var)))
		i++;
	if (env[i])
	{
		res = ft_strchr(env[i], '=');
		res++;
		return (res);
	}
	return (NULL);
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
	data->var = malloc(sizeof(char *));
	if (!data->var)
		ft_free_strs(data->env, i, 1);
	data->var[0] = NULL;
}
