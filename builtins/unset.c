/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:15:55 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/11 20:43:27 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_name(char *name)
{
	int	j;

	j = 0;
	while (name[j])
	{
		if (!ft_isalnum(name[j]) && name[j] != '_')
		{
			ft_printf(2, "unset: `%s': not a valid identifier\n", name);
			return (0);
		}
		j++;
	}
	return (1);
}

int	unset_remove(t_data *data, int idx)
{
	char	**new;
	int		i;
	int		j;

	new = malloc(ft_strslen(data->env) * sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	j = 0;
	while (data->env[j])
	{
		if (j != idx)
			new[i++] = data->env[j];
		else
			free(data->env[j]);
		j++;
	}
	new[i] = 0;
	free(data->env);
	data->env = new;
	return (0);
}

int	ft_unset(t_data *data, char **arg)
{
	char	**array;
	int		ret;
	int		idx;
	int		i;

	if (!arg[1])
		return (0);
	array = ft_split(arg[1], ' ');
	if (!array)
		return (1);
	i = 0;
	while (array[i])
	{
		if (!check_name(array[i]))
			ret = 1;
		idx = check_existence(data, array[i], ft_strlen(array[i]));
		if (idx >= 0)
			unset_remove(data, idx);
		ret = 1;
		i++;
	}
	return (ret);
}
