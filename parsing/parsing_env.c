/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:25:51 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/18 15:30:28 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	ft_free_strs(char **board, int i, int quit)
{
	while (board && board[i])
		free(board[i++]);
	free(board);
	if (quit == 1 || quit == 0)
		exit(quit);
}

void	get_env(char **env, t_data *data)
{
	char	**new;
	int		i;

	new = malloc((ft_strslen(env) + 1) * sizeof(char *));
	if (!new)
		exit (1);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			ft_free_strs(new, i, 1);
		i++;
	}
	new[i] = NULL;
	data->env = new;
	data->var = malloc(sizeof(char *));
	if (!data->var)
		ft_free_strs(data->env, i, 1);
	data->var[0] = NULL;
}
