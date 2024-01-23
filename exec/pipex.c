/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:27:48 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/23 12:05:03 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipex(t_data *data, int i, int *end)
{
	if (!data->pid)
	{
		close(end[1]);
		close(end[0]);
		enable_signal_print();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (data->exec[i].infile == -1 || data->exec[i].outfile == -1)
			exit (1);
		if (is_builtins(data->exec[i].argv[0]))
		{
			exec_builtins(data, is_builtins(data->exec[i].argv[0]), i);
			exit (data->status);
		}
		else if (execve(data->exec[i].path, data->exec[i].argv, data->env) == -1)
		{
			ft_printf(2, "minishell: %s: command not found\n", data->exec[i].argv[0]);
			// perror("");
			exit (COM_NOT_FOUND);
		}
	}
	else
	{
		signal(SIGQUIT, sig_quit);
		signal(SIGINT, sig_interrupt_exec);
		close(end[1]);
		if (data->exec[i].infile <= 2)
			dup2(end[0], STDIN_FILENO);
		close(end[0]);
	}
}

void	ft_init_pipex(t_data *data, int i, int stdout_cpy)
{
	int		end[2];
	
	if (pipe(end) == -1)
	{
		perror("Pipe");
		exit (-1); // A CHANGER
	}
	if (data->exec[i].infile > 2)
		dup2(data->exec[i].infile, STDIN_FILENO);
	if (data->exec[i].outfile > 2) 
		dup2(data->exec[i].outfile, STDOUT_FILENO);
	else if (data->exec[i + 1].argv)
		dup2(end[1], STDOUT_FILENO);
	else
		dup2(stdout_cpy, STDOUT_FILENO);
	data->pid = fork();
	if (data->pid < 0)
		ft_crash(data);
	ft_pipex(data, i, end);
}
