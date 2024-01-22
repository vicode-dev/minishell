/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:22:10 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/22 17:52:44 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_struct_env(t_env *env)
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

static int	find_next(t_env *env, int i, int k)
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

static void	print_env2(t_env *env, int j)
{
	if (env[j].content)
		ft_printf(1, "declare -x %s=\"%s\"\n", env[j].name, env[j].content);
	else
		ft_printf(1, "declare -x %s\n", env[j].name);
}

int	print_env(t_data *data)
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
	print_env2(env, j);
	while (i-- > 1)
	{
		j = find_next(env, j, k);
		print_env2(env, j);
	}
	free_struct_env(env);
	return (0);
}
