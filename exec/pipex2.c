/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:27:48 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/17 18:33:28 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipex(t_data *data, int i, int *end)
{
	if (!data->pid)
	{
		close(end[1]);
		close(end[0]);
		if (data->exec[i].infile == -1 || data->exec[i].outfile == -1)
			exit (1);

		if (execve(data->exec[i].path, data->exec[i].argv, data->env) == -1)
		{
			printf("Command not found\n");
			exit (1);
		}
	}
	else
	{
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
	if (data->exec[i].infile > -1)
		dup2(data->exec[i].infile, STDIN_FILENO);
	if (data->exec[i].outfile > 2)
		dup2(data->exec[i].outfile, STDOUT_FILENO);
	else if (data->exec[i + 1].argv)
		dup2(end[1], STDOUT_FILENO);
	else
		dup2(stdout_cpy, STDOUT_FILENO);
	data->pid = fork();
	if (data->pid < 0)
		return ; // A CHANGER
	ft_pipex(data, i, end);
	
}
