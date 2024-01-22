/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:29:22 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/22 17:59:38 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_structlen(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
		i++;
	return (i);
}

char	**struct_to_array(t_env *env)
{
	char	**array;
	char	*line;
	char	*temp;
	int		i;

	array = malloc((ft_structlen(env) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (env[i].name)
	{
		temp = ft_strjoin(env[i].name, "=");
		line = ft_strjoin(temp, env[i].content);
		free(temp);
		if (!line)
		{
			array[i] = 0;
			return (ft_free_strs(array, 0, 2), NULL);
		}
		array[i] = line;
		i++;
	}
	array[i] = NULL;
	return (array);
}

t_env	*array_to_struct(t_data *data)
{
	t_env	*new;
	char	*temp;
	int		i;

	new = malloc((ft_strslen(data->env) + 1) * sizeof(t_env));
	if (!new)
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		new[i].name = ft_strdup(data->env[i]);
		if (!new[i].name)
			return (free_struct_env(new), NULL);
		temp = ft_strchr(new[i].name, '=');
		if (temp)
			*temp = 0;
		if (temp)
			new[i].content = ft_strdup(++temp);
		else
			new[i].content = NULL;
		i++;
	}
	new[i].name = NULL;
	return (new);
}
