/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:44:54 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/17 16:04:06 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(t_data *data, char *str, int i)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (2);
	else if (!ft_strcmp(str, "env"))
		return (3);
	else if (!ft_strcmp(str, "export"))
		return (4);
	else if (!ft_strcmp(str, "pwd"))
		return (5);
	else if (!ft_strcmp(str, "unset"))
		return (6);
	else if (!ft_strcmp(str, "exit") && i == 0 && !data->exec[i + 1].argv)
		return (7);
	else
		return (0);
}

// void	exec_builtins(t_data *data, int type, int i)
// {
// 	if (type == 1)
// 		ft_echo(data, data->exec[i]);
// 	else if (!ft_strcmp(str, "cd"))
// 		return (2);
// 	else if (!ft_strcmp(str, "env"))
// 		return (3);
// 	else if (!ft_strcmp(str, "export"))
// 		return (4);
// 	else if (!ft_strcmp(str, "pwd"))
// 		return (5);
// 	else if (!ft_strcmp(str, "unset"))
// 		return (6);
// 	else if (!ft_strcmp(str, "exit") && i == 0 && !data->exec[i + 1].argv)
// 		return (7);
// }

// static int	ft_execlen(t_exec *exec)
// {
// 	int	i;

// 	i = 0;
// 	while (exec[i].argv)
// 		i++;
// 	return (i);
// }

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		j;

	paths = ft_split(get_env_var(env, "PATH"), ':');
	j = 0;
	while (paths && paths[j])
	{
		temp = ft_strjoin(paths[j], "/");
		free(paths[j]);
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK | X_OK) != -1)
			return (ft_free_strs(paths, j + 1, 2), path);
		free(path);
		j++;
	}
	return (free(paths), NULL);
}

char	*parse_path(t_data *data, int i)
{
	char	*path;

	if (access(data->exec[i].argv[0], F_OK | X_OK) != -1)
		path = ft_strdup(data->exec[i].argv[0]);
	else
		path = get_path(data->exec[i].argv[0], data->env);
	return (path);
}

int	executer(t_data *data)
{
	// ["ls", "-la", "cat"]
	int		i;
	int		builtin;
	int		status;
	int		stdin_cpy;
	int		stdout_cpy;

	i = 0;
	builtin = is_builtins(data, data->exec[i].argv[0], i);
	if (builtin && !data->exec[1].argv)
	{
		// exec_builtins(data, builtin, i);
		i++;
	}
	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	while (data->exec[i].argv)
	{
		data->exec[i].path = parse_path(data, i);
		ft_init_pipex(data, i, stdout_cpy);
		i++;
	}
	dup2(stdin_cpy, 0);
	dup2(stdout_cpy, 1);
	close(stdin_cpy);
	close(stdout_cpy);
	waitpid(data->pid, &status, 0);
	data->status = WEXITSTATUS(status);
	return (0);
}
