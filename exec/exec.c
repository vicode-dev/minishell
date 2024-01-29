/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:44:54 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/29 10:48:47 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

/**
 * @brief parse argv[0] and find a command path or print error message
 * 
 * @param data 
 * @param i index in exec array
 * @return char* if there is a valid command path or NULL
 */
static char	*parse_path(t_data *data, int i)
{
	if (!data->exec[i].argv[0])
		return (NULL);
	if (is_builtins(data->exec[i].argv[0]))
		return (NULL);
	if ((data->exec[i].argv[0][0] == '/') || 
		(data->exec[i].argv[0][0] == '.' && data->exec[i].argv[0][1] == '/'))
	{
		data->status = CANNOT_EXEC;
		if (access(data->exec[i].argv[0], F_OK | X_OK) != -1)
		{
			if (is_directory(data->exec[i].argv[0]))
				return (ft_printf(2, "minishell: %s: is a directory\n",
						data->exec[i].argv[0]), NULL);
			return (ft_strdup(data->exec[i].argv[0]));
		}
		ft_printf(2, "minishell: %s: %s\n",
			data->exec[i].argv[0], strerror(errno));
		if (access(data->exec[i].argv[0], F_OK) == -1)
			data->status = COM_NOT_FOUND;
		return (NULL);
	}
	return (get_path(data, data->exec[i].argv[0], data->env));
}

static void	receive_sig(t_data *data)
{
	if (g_signal == SIGINT)
	{
		data->status = INTERRUPT_SIG;
		g_signal = 0;
	}
	if (g_signal == SIGQUIT)
	{
		data->status = QUIT_SIG;
		g_signal = 0;
	}
}

/**
 * @brief wait the number of child process that has been fork
 * 
 * @param data 
 */
static void	waits(t_data *data)
{
	int	i;

	i = 0;
	while (i < tab_size(data->list))
	{
		wait(NULL);
		i++;
	}
}

static void	executer_handler(t_data *data, int stdout_cpy)
{
	int	i;

	i = 0;
	while (data->exec[i].argv)
	{
		data->exec[i].path = parse_path(data, i);
		ft_init_pipex(data, i, stdout_cpy);
		i++;
	}
}

/**
 * @brief minishell execution part
 * 
 * @param data 
 */
void	executer(t_data *data)
{
	int		builtin;
	int		status;
	int		stdin_cpy;
	int		stdout_cpy;

	builtin = is_builtins(data->exec[0].argv[0]);
	if (builtin && !data->exec[1].argv)
	{
		redirect_exec_builtins(data, builtin, 0);
		return ;
	}
	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	executer_handler(data, stdout_cpy);
	dup2(stdin_cpy, 0);
	dup2(stdout_cpy, 1);
	close(stdin_cpy);
	close(stdout_cpy);
	waitpid(data->pid, &status, 0);
	data->status = WEXITSTATUS(status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_interrupt);
	disable_signal_print();
	receive_sig(data);
	waits(data);
}
