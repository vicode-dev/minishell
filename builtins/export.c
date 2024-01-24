/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:39:28 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/24 13:03:25 by vilibert         ###   ########.fr       */
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

void	ft_export(t_data *data, char **vars)
{
	int		j;
	int		ret;

	ret = 0;
	j = 1;
	if (!vars[j])
		ret = print_env(data);
	else
	{
		while (vars[j])
		{
			if (export_parse(data, vars[j]) == 1)
				ret = 1;
			j++;
		}
	}
	data->status = ret;
}
