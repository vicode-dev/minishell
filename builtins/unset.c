/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:15:55 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/24 13:35:34 by vilibert         ###   ########.fr       */
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
			ft_printf(2, "minishell: unset: `%s': not a valid identifier\n", 
				name);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	unset_remove(t_data *data, int idx)
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

void	ft_unset(t_data *data, char **arg)
{
	int		ret;
	int		idx;
	int		i;

	if (!arg[1])
	{
		data->status = 0;
		return ;
	}
	i = 0;
	ret = 0;
	while (arg[i])
	{
		if (!check_name(arg[i]))
			ret = 1;
		idx = check_existence(data, arg[i], ft_strlen(arg[i]));
		if (idx >= 0)
			ret = unset_remove(data, idx);
		i++;
	}
	data->status = ret;
}
