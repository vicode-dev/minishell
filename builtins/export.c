/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:39:28 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/09 15:04:38 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

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
			&& ft_strcmp(env[j].name, env[next].name) > 0
			&& ft_strcmp(env[next].name, "_") != 0)
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
	while (i-- > 2)
	{
		j = find_next(env, j, k);
		print_env2(env, j, f[1]);
	}
	free_struct(env);
	return (0);
}

int	ft_export(t_data *data, char **vars, int *in_out)
{
	if (!vars[1])
		print_env(data, in_out);
	// else
	// 	export_parse(data, vars, in_out);
	return (0);
}
