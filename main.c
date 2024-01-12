/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:25:35 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/12 15:44:19 by vilibert         ###   ########.fr       */
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
	exit (g_exitcode);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	g_exitcode = 0;
	data.exec = 0;
	data.the_array = 0;
	get_env(env, &data);
	prompt_reader(&data);
}
