/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:21:02 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/18 18:52:11 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_name(char *str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if ((!ft_isalnum(str[j]) && str[j] != '_') || 
			(j == 0 && !ft_isalpha(str[j]) && str[j] != '_'))
		{
			ft_printf(2, "minishell: export: `%s': not a valid identifier\n", 
				str);
			return (0);
		}
		j++;
	}
	if (str[j] == '+' && str[j + 1] != '=')
	{
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", str);
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

int	export_parse(t_data *data, char *var)
{
	int		i;
	int		exist;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
		i++;
	if (!check_name(var, i))
		return (1); // Error : name invalid
	exist = check_existence(data, var, i);
	if (exist >= 0)
		export_replace(data, var, exist, i);
	else
		export_add(data, var);
	return (0);
}
