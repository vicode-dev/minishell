/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:36:00 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/18 18:02:48 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*get_prompt(t_data *data)
{
	char	*tmp;
	char	*cwd;
	char	*prompt;

	prompt = ft_strjoin(get_env_var(data->env, "USER"), " ");
	if (!prompt)
		return(ft_strdup("minishell % "));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		free(prompt);
	if (!cwd)
		ft_crash(data);
	tmp = ft_strrchr(cwd, '/');
	tmp = ft_strjoin(prompt, ++tmp);
	free(prompt);
	free(cwd);
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
		if (!line)
			ft_crash(data);
		free(prompt);
		data->list = lexer(data, &line);
		add_history(line);
		expander(data);
		parse(data);
		if (data->exec)
			executer(data);
		ft_free_lexed(&(data->list));
		free(data->exec); // a changer par une fonction de clean correct
		data->exec = NULL;
		free(line);
	}
	return (0);
}
