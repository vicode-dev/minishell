/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:25:35 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/11 15:27:34 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exitcode;

//For malloc crash
void	ft_crash(t_data *data)
{
	g_exitcode = 1;
	ft_free_lexed(&(data->list));
	free(data->exec);
	ft_exit_prog(data);
}

void	ft_exit_prog(t_data *data)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
		free(data->env[i++]);
	free(data->env);
	// rl_clear_history();
	i = 0;
	// while (data->var && data->var[i])
	// 	free(data->var[i]);
	// free(data->var);
	exit (g_exitcode);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)(argc + (int)argv);
	g_exitcode = 0;
	data.exec = 0;
	get_env(env, &data);
	prompt_reader(&data);
}
