/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:25:35 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/18 16:34:45 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exitcode;

//For malloc crash
void	ft_crash(t_data *data)
{
	g_exitcode = 1;
	ft_exit_prog(data);
}
void	ft_free_lexed(t_lexed **list)
{
	t_lexed	*tmp;

	while (*list && (*list)->prev)
		*list = (*list)->prev;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->word);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	ft_exit_prog(t_data *data)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
		free(data->env[i++]);
	free(data->env);
	if (data->the_array)
		ft_free_strs(data->the_array, 0, 2);
	ft_free_lexed(&(data->list));
	free(data->exec);
	// rl_clear_history();
	exit (data->status);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	g_exitcode = 0;
	data.exec = 0;
	data.the_array = 0;
	data.list = NULL;
	data.status = 0;
	data.pid = 0;
	get_env(env, &data);
	prompt_reader(&data);
}
