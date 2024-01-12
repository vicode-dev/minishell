/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:04:07 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/12 15:40:45 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tab_size(t_lexed *list)
{
	int	count;

	count = 1;
	while (list->next)
	{
		if (list->token == PIPE)
			count++;
		list = list->next;
	}
	return (count);
}

char	**join(t_data *data, char ***w_split, int *i)
{
	char	*tmp;

	*i = ft_strslen(data->the_array) - 1;
	tmp = ft_strjoin(data->the_array[*i], *w_split[0]);
	if (!tmp)
	{
		ft_free_strs(*w_split, 0, 2);
		ft_crash(data);
	}
	free(*w_split[0]);
	free(data->the_array[*i]);
	data->the_array[*i] = tmp;
	(*w_split)++;
	return (data->the_array);
}

void	create_the_array_word(t_data *data, t_lexed **list)
{
	char	**w_split;
	char	**tmp_array;
	int		i;

	w_split = ft_split((*list)->word, ' ');
	i = -10;
	if (!w_split)
		ft_crash(data);
	if ((*list)->prev && (*list)->prev->token != PIPE 
		&& (*list)->word[0] != ' ')
		data->the_array = join(data, &w_split, &i);
	tmp_array = ft_arrayjoin(data->the_array, w_split, ft_strslen(w_split));
	if (!tmp_array)
	{
		ft_free_strs(w_split, 0, 2);
		ft_crash(data);
	}
	free(data->the_array);
	if (i != -10)
		w_split--;
	free(w_split);
	data->the_array = tmp_array;
}

void	create_the_array_quot(t_data *data, t_lexed **list)
{
	char	*tmp;
	char	**tmp_array;
	int		i;

	if (((*list)->prev && (*list)->prev->token == WORD 
			&& (*list)->prev->word[ft_strlen((*list)->prev->word) - 1] == ' ')
		|| !(*list)->prev)
	{
		tmp = ft_strdup((*list)->word);
		tmp_array = ft_arrayjoin(data->the_array, &tmp, 1);
		free(data->the_array);
	}
	else
	{
		i = ft_strslen(data->the_array) - 1;
		tmp = ft_strjoin(data->the_array[i], (*list)->word);
		free(data->the_array[i]);
		if (!tmp)
			ft_crash(data);
		data->the_array[i] = tmp;
		tmp_array = data->the_array;
	}
	data->the_array = tmp_array;
}

void	create_the_array(t_data *data, t_lexed **list)
{
	data->the_array = ft_calloc(1, sizeof(char *));
	while ((*list) && (*list)->token != PIPE)
	{
		if ((*list)->token == WORD)
			create_the_array_word(data, list);
		else if ((*list)->token == DQUOTE || (*list)->token == SQUOTE)
			create_the_array_quot(data, list);
		*list = (*list)->next;
	}
	int i=0;
	while(data->the_array[i])
		ft_printf(1, "%s.\n", data->the_array[i++]);
}

void	parse_heredoc(t_data *data, int idx, int *i, int *j)
{
	int		doc;
	char	*eof;
	char	*buff;

	doc = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 00777);
	if (!data->the_array[*i][*j + 2])
		eof = data->the_array[*i + 1];
	else
		eof = &(data->the_array[*i][*j + 2]);
	buff = readline(">");
	if (!buff)
		ft_crash(data);
	while (ft_strncmp(buff, eof, ft_strlen(buff)))
	{
		//expander here_doc(data, ...)
		ft_printf(doc, "%s\n", buff);
		free(buff);
		buff = readline(">");
		if (!buff)
			ft_crash(data);
	}
	close(data->exec[idx].infile);
	data->exec[idx].infile = doc;
}

// void	parse_infile(t_data *data, char **the_array, )

void	parse_in(t_data *data, int idx, int *i, int *j)
{
	if (data->the_array[*i][*j + 1] == '<')
		parse_heredoc(data, idx, i, j);
	// else
	// 	parse_infile();
}

void	fill_exec(t_data *data, int idx)
{
	int	i;
	int	j;

	i = 0;
	while (data->the_array[i])
	{
		j = 0;
		while (data->the_array[i][j])
		{
			if (data->the_array[i][j] == '<')
				parse_in(data, idx, &i, &j);
			// else if (the_array[ij[0]][ij[1]] == '>')
			// 	parse_out();
			// else
			// 	parse_argv();
			break ;
			j++;
		}
		break ;
		i++;
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

void	parse(t_data *data)
{
	int		exec_idx;
	int		exec_size;
	t_lexed	*list;

	list = data->list;
	if (!list)
		return ;
	exec_size = tab_size(list);
	data->exec = malloc(exec_size * sizeof(t_exec));
	if (!data->exec)
		ft_crash(data);
	init_exec(data, exec_size);
	exec_idx = 0;
	while (exec_idx < 1)
	{
		create_the_array(data, &list);
		fill_exec(data, exec_idx);
		exec_idx++;
	}
	free(data->exec);
	data->exec = NULL;
	ft_free_strs(data->the_array, 0, 2);
	data->the_array = NULL;
	// while (list->next)
	// {
	// 	j = 0;
	// 	while (list->word && list->word[j])
	// 	{
	// 		if (list->word[j] == '<')
	// 			//trouver infile
	// 		else if (list->word[j] == '>')
	// 			//trouver outfile
	// 		else if 
	// 	}
	// }
}
