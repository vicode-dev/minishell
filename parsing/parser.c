/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:04:07 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/25 12:26:59 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	parse_ioa(t_data *data, int idx, t_lexed *list)
{
	int	fd;

	fd = -1;
	if (data->exec[idx].infile == -1 || data->exec[idx].outfile == -1)
		return ;
	else if (list->token == INFILE)
		fd = open(list->word, O_RDONLY);
	else if (list->token == OUTFILE)
		fd = open(list->word, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	else if (list->token == APPEND)
		fd = open(list->word, O_WRONLY | O_CREAT | O_APPEND, 00777);
	if (fd == -1)
		ft_printf(2, "minishell: %s: %s\n", list->word, strerror(errno));
	if (fd == -1)
		data->status = 1;
	if (list->token == INFILE && data->exec[idx].infile > 2)
		close(data->exec[idx].infile);
	else if (list->token != INFILE && data->exec[idx].outfile > 2)
		close(data->exec[idx].outfile);
	if (list->token == INFILE)
		data->exec[idx].infile = fd;
	else if (list->token == OUTFILE || list->token == APPEND)
		data->exec[idx].outfile = fd;
	else
		close(fd);
}

void	create_the_array(t_data *data, t_lexed **list, int exec_idx)
{
	data->the_array = ft_calloc(1, sizeof(char *));
	while ((*list) && (*list)->token != PIPE)
	{
		if ((*list)->token == INFILE || (*list)->token == OUTFILE
			|| (*list)->token == APPEND)
			parse_ioa(data, exec_idx, (*list));
		else if ((*list)->token == HERE_DOC)
			here_doc(data, exec_idx, (*list));
		else if ((*list)->token == WORD)
			create_the_array_word(data, list);
		else if ((*list)->token == DQUOTE || (*list)->token == SQUOTE)
			create_the_array_quot(data, list);
		if (g_signal == SIGINT)
			return ;
		*list = (*list)->next;
	}
}

void	init_exec(t_data *data, int exec_size)
{
	int	i;

	i = 0;
	while (i < exec_size)
	{
		data->exec[i].infile = 0;
		data->exec[i].outfile = 1;
		data->exec[i].path = NULL;
		data->exec[i].argv = NULL;
		i++;
	}
}

/**
 * @brief Transform list into the exec array
 * 
 * @param data 
 */
void	parse(t_data *data)
{
	int		exec_idx;
	int		exec_size;
	t_lexed	*list;

	list = data->list;
	if (!list)
		return ;
	exec_size = tab_size(list);
	data->exec = malloc((exec_size + 1) * sizeof(t_exec));
	if (!data->exec)
		ft_crash(data);
	init_exec(data, exec_size + 1);
	exec_idx = 0;
	while (exec_idx < exec_size)
	{
		create_the_array(data, &list, exec_idx);
		data->exec[exec_idx].argv = data->the_array;
		data->the_array = NULL;
		exec_idx++;
		if (g_signal == SIGINT)
			return ;
		if (list)
			list = list->next;
	}
}
