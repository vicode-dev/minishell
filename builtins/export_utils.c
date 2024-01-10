/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:29:22 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/10 15:31:22 by jgoudema         ###   ########.fr       */
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
	// if (!array)
	// 	?
	i = 0;
	while (env[i].name)
	{
		temp = ft_strjoin(env[i].name, "=");
		// if (!temp)
		// ?
		line = ft_strjoin(temp, env[i].content);
		// if (!line)
		// 	?
		free(temp);
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
	char	*temp2;
	int		i;

	new = malloc((ft_strslen(data->env) + 1) * sizeof(t_env));
	// if (!new)
	// 	exit (1); ?
	i = 0;
	while (data->env[i])
	{
		temp2 = ft_strdup(data->env[i]);
		temp = ft_strchr(temp2, '=');
		if (temp)
			*temp = 0;
		new[i].name = ft_strdup(temp2);
		if (temp)
			new[i].content = ft_strdup(++temp);
		else
			new[i].content = 0;
		// ft_printf(1, "data %s, temp %s, name %s, content %s\n\n", data->env[i], temp, new[i].name, new[i].content);
		// if (!new[i].name)
		// 	ft_free_strs(new, i, 1); ?
		free(temp2);
		i++;
	}
	new[i].name = NULL;
	return (new);
}
