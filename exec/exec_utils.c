/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:30:14 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/25 11:34:21 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief check if the string correspond to a builtin 
 * command call and return a specific int for each
 * @param str a NULL terminated string to scan
 * @return int from 1 to 7 in case of builtins and 0 if not
 */
int	is_builtins(char *str)
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
	else if (!ft_strcmp(str, "exit"))
		return (7);
	else
		return (0);
}

void	exec_builtins(t_data *data, int type, int i)
{
	if (data->exec[i].infile == -1)
		data->status = 1;
	else if (type == 1)
		ft_echo(data, data->exec[i].argv);
	else if (type == 2)
		ft_cd(data, data->exec[i].argv);
	else if (type == 3)
		ft_env(data);
	else if (type == 4)
		ft_export(data, data->exec[i].argv);
	else if (type == 5)
		ft_pwd(data);
	else if (type == 6)
		ft_unset(data, data->exec[i].argv);
	else if (type == 7)
		ft_exit(data, data->exec[i].argv);
}

void	redirect_exec_builtins(t_data *data, int type, int i)
{
	int	stdin_cpy;
	int	stdout_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	if (data->exec[i].infile > -1)
		dup2(data->exec[i].infile, STDIN_FILENO);
	if (data->exec[i].outfile > 2)
		dup2(data->exec[i].outfile, STDOUT_FILENO);
	exec_builtins(data, type, i);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
}

char	*get_path(t_data *data, char *cmd, char **env)
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
	ft_printf(2, "minishell: %s: command not found\n", cmd);
	data->status = COM_NOT_FOUND;
	return (free(paths), NULL);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
