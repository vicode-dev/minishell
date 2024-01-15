/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:44:54 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/15 18:52:21 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(t_data *data, char *str, int i)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	// else if (!ft_strcmp(str, "cd"))
	// 	return (2);
	else if (!ft_strcmp(str, "env"))
		return (3);
	else if (!ft_strcmp(str, "export"))
		return (4);
	else if (!ft_strcmp(str, "pwd"))
		return (5);
	else if (!ft_strcmp(str, "unset"))
		return (6);
	else if (!ft_strcmp(str, "exit") && i == 0 && !data->exec[i + 1].argv)
		return (7);
	else
		return (0);
}

int	executer(t_data *data)
{
	// ["ls", "-la", "cat"]
	int	i;

	i = 0;
	while (data->exec[i].argv)
	{
		if (!is_builtins(data, data->exec[i].argv[0], i))
			ft_pipex();
		i++;
	}
}
