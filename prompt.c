/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:36:00 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 15:33:33 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

char	*get_prompt(t_data *data)
{
	char	*tmp;
	char	*cwd;
	char	*prompt;

	prompt = ft_strjoin(get_env_var(data->env, "USER"), " ");
	if (!prompt)
		return (ft_strdup("minishell % "));
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		tmp = ft_strrchr(cwd, '/');
		tmp = ft_strjoin(prompt, ++tmp);
		free(cwd);
		free(prompt);
	}
	else
		tmp = prompt;
	if (!tmp)
		ft_crash(data);
	prompt = ft_strjoin(tmp, " % ");
	free(tmp);
	if (!prompt)
		ft_crash(data);
	return (prompt);
}

int	prompt_reader(t_data *data)
{
	int		again;
	char	*line;
	char	*prompt;

	again = 1;
	while (again)
	{
		prompt = get_prompt(data);
		line = readline(prompt);
		free(prompt);
		if (!line)
			ft_crash(data);
		if (!check_syntax_error(data, line))
			lexer(data, &line);
		add_history(line);
		if (g_signal != SIGINT && data->list && !syntax_checker(data, data->list))
		{
			expander(data);
			parse(data);
			if (data->exec && data->exec[0].argv[0])
				executer(data);
		}
		ft_free_cycle(data);
		g_signal = 0;
		free(line);
	}
	return (0);
}
