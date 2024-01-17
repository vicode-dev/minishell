/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:39:28 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/17 13:48:07 by jgoudema         ###   ########.fr       */
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
	int		j;
	int		ret;

	ret = 0;
	j = 1;
	if (!vars[j])
		print_env(data, out);
	else
	{
		while (vars[j])
		{
			ret = export_parse(data, vars[j], out);
			j++;
		}
	}
	return (ret);
}
