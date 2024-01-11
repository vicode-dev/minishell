/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:41:26 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/11 10:38:43 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (1);
	return (0);
}

int	export_add(t_data *data, char *arg)
{
	char	**new_env;
	char	*line;

	line = ft_strdup(arg);
	if (!line)
		return (1);
	new_env = ft_arrayjoin(data->env, &line, 1);
	if (!new_env)
		return (free(line), 1);
	free(data->env);
	data->env = new_env;
	return (0);
}

int	export_replace(t_data *data, char *arg, int pos, int i)
{
	char	*temp;
	char	*new;

	if (arg[i++] == '+')
	{
		i++;
		if (!find(data->env[pos], '='))
		{
			new = ft_strjoin(data->env[pos], "=");
			free(data->env[pos]);
			data->env[pos] = new;
		}
		temp = ft_substr(arg, i, ft_strlen(arg) - i);
		new = ft_strjoin(data->env[pos], temp);
		free(temp);
		free(data->env[pos]);
		data->env[pos] = new;
	}
	else
	{
		i++;
		free(data->env[pos]);
		data->env[pos] = ft_strdup(arg);
	}
	return (0);
}
