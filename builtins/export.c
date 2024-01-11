/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:39:28 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/11 20:26:38 by jgoudema         ###   ########.fr       */
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

int	ft_export(t_data *data, char **vars, int out)
{
	char	**array;
	int		i;

	if (!vars[1])
		print_env(data, out);
	else
	{
		array = ft_split(vars[1], ' ');
		if (!array)
			return (1);
		i = 0;
		while (array[i])
		{
			export_parse(data, array[i], out);
			i++;
		}
	}
	return (0);
}
