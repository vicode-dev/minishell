/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:19:48 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/09 18:42:02 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Initialize the struct */

#include "minishell_temp.h"

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	ft_free_strs(t_env *env, int i, int quit)
{
	while (i >= 0)
	{
		free(env[i--].name);
	}
	free(env);
	if (quit == 1 || quit == 0)
		exit(quit);
}

void	get_env(char **env, t_data *data)
{
	t_env	*new;
	char	*temp;
	int		i;

	new = malloc((ft_strslen(env) + 1) * sizeof(t_env));
	if (!new)
		exit (1);
	i = 0;
	while (env[i])
	{
		temp = ft_strchr(env[i], '=');
		*temp = 0;
		new[i].name = ft_strdup(env[i]);
		new[i].content = ft_strdup(++temp);
		// if (!new[i].name)
		// 	ft_free_strs(new, i, 1);
		i++;
	}
	new[i].name = NULL;
	data->env = new;
	// data->var = malloc(sizeof(char *));
	// if (!data->var)
	// 	ft_free_strs(data->env, i, 1);
	// data->var[0] = NULL;
}
