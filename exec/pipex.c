/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:27:48 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/16 18:14:14 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipex(t_data *data, int i, int *end)
{
	int	status;

	if (!data->pid)
	{
		// if (data->f1 == -1 && i == 0)
		// 	exit (1);
		// dup2(end[1], data->exec[i].infile);
		close(end[0]);
		if (execve(data->exec[i].path, data->exec[i].argv, data->env) == -1)
		{
			// ft_free_data(data);
			printf("Command not found\n");
			exit (1);
		}
	}
	else
	{
		close(end[1]);
		waitpid(data->pid, &status, 0);
		data->status = WEXITSTATUS(status);
		// dup2(end[0], data->exec[i].outfile);
		return ;
	}
}

void	ft_init_pipex(t_data *data, int i)
{
	int		end[2];

	if (pipe(end) == -1)
	{
		perror("Pipe");
		exit (-1);
	}
	data->pid = fork();
	if (data->pid < 0)
		return ;
	ft_pipex(data, i, end);
}
