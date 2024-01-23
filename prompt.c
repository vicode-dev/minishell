/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:36:00 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 17:21:33 by vilibert         ###   ########.fr       */
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
	char	*prompt;

	again = 1;
	while (again)
	{
		prompt = get_prompt(data);
		data->line = readline(prompt);
		free(prompt);
		if (!data->line)
			ft_crash(data);
		if (!check_syntax_error(data, data->line))
			lexer(data, &(data->line));
		add_history(data->line);
		if (g_signal != SIGINT && data->list 
			&& !syntax_checker(data, data->list))
		{
			expander(data);
			parse(data);
			if (data->exec && data->exec[0].argv[0])
				executer(data);
		}
		ft_free_cycle(data);
	}
	return (0);
}
