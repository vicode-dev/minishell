/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:21:02 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/12 16:43:15 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_name(char *name, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if ((!ft_isalnum(name[j]) && name[j] != '_') || 
			(j == 0 && !ft_isalpha(name[j]) && name[j] != '_'))
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", name);
			return (0);
		}
		j++;
	}
	if (name[j] == '+' && name[j + 1] != '=')
	{
		ft_printf(2, "export: `%s': not a valid identifier\n", name);
		return (0);
	}
	return (1);
}

int	check_existence(t_data *data, char *var, int i)
{
	int	j;

	j = 0;
	while (data->env[j])
	{
		if (!ft_strncmp(data->env[j], var, i) && (data->env[j][i] == 0 
			|| data->env[j][i] == '='))
			return (j);
		j++;
	}
	return (-1);
}

int	check_dollar(t_data *data, char *var, int i, int out)
{
	int	start;

	start = i;
	while (var[i] && ft_isalnum(var[i]))
		i++;
	if ((i == start && var[i] == 0) || (var[i] != 0 && var[i] != '_')) // WTF
	{
		ft_printf(2, "export: `%s': not a valid identifier\n", var);
		return (1);
	}
	else
		print_env(data, out);
	return (0);
}

int	export_parse(t_data *data, char *var, int out)
{
	int		i;
	int		exist;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+'
			&& var[i] != '$')
		i++;
	if (var[i] == '$')
		return (check_dollar(data, var, i + 1, out));
	if (!check_name(var, i))
		return (1); // Error : name invalid
	exist = check_existence(data, var, i);
	if (exist >= 0)
		export_replace(data, var, exist, i);
	else
		export_add(data, var);
	return (0);
}
