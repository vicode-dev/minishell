/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:47:41 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/11 15:47:44 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

static char	***ft_parse_args(t_data *data, char **argv)
{
	char	***args;
	int		i;
	int		j;

	args = malloc((data->count + 1) * sizeof(char **));
	if (!args)
		return (NULL);
	i = 1;
	j = 0;
	while (argv[++i] && argv[i + 1])
	{
		args[j] = ft_split(argv[i], ' ');
		if (!args[j])
		{
			while (j >= 0)
				ft_free_strs(args[j--], 0);
			return (free(args), NULL);
		}
		j++;
	}
	args[j] = 0;
	return (args);
}

static char	**ft_parse_path(t_data *data, char ***args, char **envp)
{
	char	**paths;
	int		i;
	int		j;

	paths = malloc((data->count + 1) * sizeof(char *));
	if (!paths)
		return (0);
	i = -1;
	j = 0;
	while (args[++i])
	{
		if (access(args[i][0], F_OK | X_OK) != -1)
			paths[j] = ft_strdup(args[i][0]);
		else
			paths[j] = ft_get_path(args[i][0], envp);
		j++;
	}
	paths[j] = 0;
	return (paths);
}

void	ft_parse(t_data *data, char **argv, char **envp)
{
	int	i;

	data->args = ft_parse_args(data, argv);
	if (!data->args)
		exit (-1);
	data->cmds = ft_parse_path(data, data->args, envp);
	if (!data->cmds)
	{
		i = 0;
		while (data->args[i])
			ft_free_strs(data->args[i++], 0);
		free(data->args);
		exit (1);
	}
}
