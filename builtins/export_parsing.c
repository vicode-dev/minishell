/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:21:02 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/10 12:07:16 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char *name, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (!ft_isalnum(name[j]) && name[j] != '_')
		{
			ft_printf(1, "export: `%s': not a valid identifier\n", name);
			return (0);
		}
		j++;
	}
	if (name[j] == '+' && name[j + 1] != '=')
	{
		ft_printf(1, "export: `%s': not a valid identifier\n", name);
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
		if (!ft_strncmp(data->env[j], var, i))
			return (j);
		j++;
	}
	return (-1);
}

int	export_parse(t_data *data, char **vars, int *in_out)
{
	int		i;
	int		exist;

	i = 0;
	(void) in_out;
	while (vars[1][i] && vars[1][i] != '=' && vars[1][i] != '+')
		i++;
	if (!check_name(vars[1], i))
		return (1); // Error : name invalid
	exist = check_existence(data, vars[1], i);
	if (exist >= 0)
		export_replace(data, vars[1], exist, i);
	else
		export_add(data, vars[1]);
	return (0);
}
