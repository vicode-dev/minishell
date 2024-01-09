/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:36:00 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/09 15:03:44 by jgoudema         ###   ########.fr       */
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
		ft_crash(data);
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
	t_lexed	*list;
	char	*line;
	char	*prompt;

	again = 1; 


	char *s[2];
	int i[2];
	i[0] = 0;
	i[1] = 1;
	s[0] = "hello";
	s[1] = 0;
	
	while (again)
	{
		prompt = get_prompt(data);
		line = readline(prompt);
		free(prompt);
		list = lexer(data, &line);
		add_history(line);
		expander(data, list);
		while (list)
		{
			printf("%s\n", list->word);
			list = list->next;
		}
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);
			ft_free_lexed(&list);
			ft_exit_prog(data);
		}
		if (!ft_strncmp(line, "env", 4))
			ft_env(data, 1);

		// if (!ft_strncmp(line, "export", 7))
		// 	ft_export(data, s, i);
		// ft_cd(data, line);
		// ft_printf(1, "%s\n%s\n", get_env_var(data->env, "PWD"), get_env_var(data->env, "OLDPWD"));
		// ft_pwd();
		ft_free_lexed(&list);
		free(line);
	}
	return (0);
}
