/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:44:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 16:58:16 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

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

void	here_doc_handler(t_data *data, int idx, int *end, int old_stdin)
{
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
		here_doc_handler(data, idx, end, old_stdin);
	}
}
