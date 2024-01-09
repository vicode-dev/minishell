/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:22:10 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/09 18:48:37 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		free(env[i].name);
		free(env[i].content);
		i++;
	}
	free(env);
}

int	find_next(t_env *env, int i, int k)
{
	int	j;
	int	next;

	next = 0;
	j = k;
	while (env[next].name)
	{
		if (next != i && ft_strcmp(env[i].name, env[next].name) < 0
			&& ft_strcmp(env[j].name, env[next].name) > 0)
			j = next;
		next++;
	}
	return (j);
}

void	print_env2(t_env *env, int j, int out)
{
	if (env[j].content)
		ft_printf(out, "declare -x %s=\"%s\"\n", env[j].name, env[j].content);
	else
		ft_printf(out, "declare -x %s\n", env[j].name);
}

int	print_env(t_data *data, int *f)
{
	t_env	*env;
	int		i;
	int		j;
	int		k;

	env = array_to_struct(data);
	i = -1;
	j = 0;
	k = 0;
	while (env[++i].name)
	{
		if (ft_strcmp(env[i].name, env[j].name) < 0)
			j = i;
		if (ft_strcmp(env[i].name, env[k].name) > 0)
			k = i;
	}
	print_env2(env, j, f[1]);
	while (i-- > 1)
	{
		j = find_next(env, j, k);
		print_env2(env, j, f[1]);
	}
	free_struct(env);
	return (0);
}
