/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:44:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 15:29:57 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

static char	*expand_exit_code(t_data *data, char *buff, int i)
{
	char	*tmp;
	int		len;

	tmp = ft_itoa(data->status);
	len = ft_strlen(tmp);
	tmp = ft_replace(buff, tmp, i, i + 2);
	free(buff);
	if (!tmp)
		ft_crash(data);
	buff = tmp;
	return (buff);
}

static char	*expand_env_var(t_data *data, char *buff, int i)
{
	int		j;
	char	*new;
	char	*tmp;

	j = i + 1;
	while (buff[j] && (ft_isalnum(buff[j]) || buff[j] == '_'))
		j++;
	new = ft_substr(buff, i, j - i);
	if (!new)
		ft_crash(data);
	tmp = get_env_var(data->env, new + 1);
	free(new);
	new = ft_replace(buff, tmp, i, j);
	free(buff);
	if (!new)
		ft_crash(data);
	buff = new;
	return (buff);
}

static char	*expand(t_data *data, char *buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '$' && buff[i + 1] == '?')
			buff = expand_exit_code(data, buff, i);
		else if (buff[i] == '$' && 
			(!ft_isalnum(buff[i + 1]) || buff[i + 1] == 0))
			i++;
		else if (buff[i] == '$')
			buff = expand_env_var(data, buff, i);
		else
			i++;
	}
	return (buff);
}

void	parse_heredoc(t_data *data, int idx, t_lexed *list, int *end)
{
	char	*buff;

	(void) idx;
	buff = readline(">");
	if (!buff)
		ft_crash(data);
	while (buff && ft_strcmp(buff, list->word))
	{
		buff = expand(data, buff);
		ft_printf(end[1], "%s\n", buff);
		free(buff);
		buff = readline(">");
	}
	free(buff);
	close(end[1]);
}

void	here_doc(t_data *data, int idx, t_lexed *list)
{
	int	pid;
	int	old_stdin;
	int	end[2];

	old_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sig_interrupt_exec);
	pipe(end);
	pid = fork();
	if (pid < 0)
		return ;
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		parse_heredoc(data, idx, list, end);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (g_signal == SIGINT)
			data->status = 1;
		close(end[1]);
		signal(SIGINT, sig_interrupt);
		dup2(old_stdin, STDIN_FILENO);
		if (data->exec[idx].infile > 2)
			close(data->exec[idx].infile);
		if (data->exec[idx].infile > -1)
			data->exec[idx].infile = end[0];
	}
}
