/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:25:35 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 15:39:54 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	g_signal;

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	g_signal = 0;
	disable_signal_print();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_interrupt);
	data.exec = NULL;
	data.the_array = NULL;
	data.list = NULL;
	data.status = 0;
	data.pid = 0;
	data.line = NULL;
	get_env(env, &data);
	prompt_reader(&data);
}
