/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:36:00 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/19 17:46:12 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*get_prompt(t_data *data)
{
	char	*tmp;
	char	*prompt;

	prompt = ft_strjoin(get_env_var(data->env, "USER"), " ");
	if (!prompt)
		ft_crash(data);
	tmp = ft_strrchr(get_env_var(data->env, "PWD"), '/');
	tmp = ft_strjoin(prompt, ++tmp);
	free(prompt);
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
	(void)data;   

	while (again)
	{
		prompt = get_prompt(data);
		line = readline(prompt);
		free(prompt);
		// lexer(line);
		if (!ft_strncmp(line, "exit", 5))
			ft_exit_prog(data);
		ft_cd(data, line);
		ft_printf(1, "%s\n%s\n", get_env_var(data->env, "PWD"), get_env_var(data->env, "OLDPWD"));
		ft_pwd();
		free(line);
	}
	return (0);
}
