/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:02:22 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/18 12:19:54 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

static void	ft_free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count)
	{
		ft_free_strs(data->args[i], 0);
		free(data->cmds[i]);
	}
	free(data->cmds);
	free(data->args);
}

static void	ft_pipe_last(t_data *data, int i, char **envp, int *pipe_fd)
{
	int		status;

	if (!data->pid)
	{
		dup2(data->f2, STDOUT_FILENO);
		close(pipe_fd[1]);
		if (data->f2 == -1 || execve(data->cmds[i], data->args[i], envp) == -1)
		{
			ft_free_data(data);
			exit (1);
		}
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(data->pid, &status, 0);
		data->status = WEXITSTATUS(status);
		return ;
	}
}

static void	ft_pipe(t_data *data, int i, char **envp, int *pipe_fd)
{
	if (!data->pid)
	{
		if (data->f1 == -1 && i == 0)
			exit (1);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		if (execve(data->cmds[i], data->args[i], envp) == -1)
		{
			ft_free_data(data);
			exit (1);
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
	}
}

static void	ft_pipe_init(t_data *data, int i, char **envp)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe");
		exit (-1);
	}
	data->pid = fork();
	if (data->pid < 0)
		return ;
	if (i < data->count - 1)
		ft_pipe(data, i, envp, pipe_fd);
	else
		ft_pipe_last
	(data, i, envp, pipe_fd);
}

// int	main(int argc, char *argv[], char **envp)
// {
// 	t_data	data;
// 	int		i;

// 	if (argc != 5)
// 		return (1);
// 	data = ft_init_data(argc, argv);
// 	ft_parse(&data, argv, envp);
// 	if (data.f1 != -1 || data.cmds[0])
// 		dup2(data.f1, 0);
// 	i = -1;
// 	while (++i < data.count)
// 		ft_pipe_init(&data, i, envp);
// 	ft_free_data(&data);
// 	return (data.status);
// }
