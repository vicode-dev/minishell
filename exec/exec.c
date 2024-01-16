/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:44:54 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/16 18:14:25 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(t_data *data, char *str, int i)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	// else if (!ft_strcmp(str, "cd"))
	// 	return (2);
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

void	exec_parse(t_data *data)
{
	int	i;

	i = 0;
	while (data->exec[i].argv)
	{
		data->exec[i].path = parse_path(data, i);
		i++;
	}
}

int	executer(t_data *data)
{
	// ["ls", "-la", "cat"]
	int		i;

	i = 0;
	exec_parse(data);

	// while (data->exec[i].argv)
	// {
	// 	ft_printf(1, "command : %s, path : %s\n", data->exec[i].argv[0], data->exec[i].path);
	// 	i++;
	// }
	// i = 0;
	while (data->exec[i].argv)
	{
		if (!is_builtins(data, data->exec[i].argv[0], i))
			ft_init_pipex(data, i);
		i++;
	}
	return (0);
}
