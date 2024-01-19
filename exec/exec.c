/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:44:54 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/19 16:10:14 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	else if (!ft_strcmp(str, "exit"))// && i == 0 && !data->exec[i + 1].argv)
		return (7);
	else
		return (0);
}

void	exec_builtins(t_data *data, int type, int i)
{
	if (type == 1)
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

void	executer(t_data *data)
{
	int		i;
	int		builtin;
	int		status;
	int		stdin_cpy;
	int		stdout_cpy;

	i = 0;
	builtin = is_builtins(data->exec[i].argv[0]);
	if (builtin && !data->exec[1].argv)
	{
		redirect_exec_builtins(data, builtin, i);
		return ;
	}
	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	while (data->exec[i].argv)
	{
		data->exec[i].path = parse_path(data, i);
		ft_init_pipex(data, i, stdout_cpy);
		if (is_builtins(data->exec[i].argv[0]) == 2)
			redirect_exec_builtins(data, 2, i);
		i++;
	}
	dup2(stdin_cpy, 0);
	dup2(stdout_cpy, 1);
	close(stdin_cpy);
	close(stdout_cpy);
	waitpid(data->pid, &status, 0);
	data->status = WEXITSTATUS(status);
	int j = 0;
	while(j < tab_size(data->list))
	{
		wait(NULL);
		j++;
	}
	return ;
}
