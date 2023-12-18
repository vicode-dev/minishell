/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:46:01 by jgoudema          #+#    #+#             */
/*   Updated: 2023/12/18 21:00:13 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_temp.h"

int	ft_structlen(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
		i++;
	return (i);
}

char	**struct_to_array(t_data *data)
{
	char	**array;
	char	*line;
	char	*temp;
	int		i;

	array = malloc((ft_structlen(data->env) + 1) * sizeof(char *));
	// if (!array)
	// 	?
	i = 0;
	while (data->env[i].name)
	{
		temp = ft_strjoin(data->env[i].name, "=");
		line = ft_strjoin(temp, data->env[i].content);
		free(temp);
		array[i] = line;
		i++;
	}
	array[i] = NULL;
	return (array);
}
