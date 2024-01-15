/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:04:07 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/15 14:00:44 by vilibert         ###   ########.fr       */
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
}

/**
 * @brief Find the position of the file's name or EOF delimitor in the_array
 * 
 * @param data 
 * @param i 
 * @param j 
 */
void	file_param(t_data *data, int *i, int *j)
{
	if (!data->the_array[*i][*j + 1])
	{
		(*i)++;
		*j = 0;
	}
	else if (data->the_array[*i][*j + 1])
		(*j)++;
	if (!data->the_array[*i] || !data->the_array[*i][*j])
		ft_crash(data);
}

void	parse_heredoc(t_data *data, int idx, int *i, int *j)
{
	int		doc;
	// char	*eof;
	char	*buff;

	doc = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 00777);
	if (doc == -1)
		ft_crash(data); // A changer
	file_param(data, i, j);
	buff = readline(">");
	if (!buff)
		ft_crash(data);
	while (ft_strncmp(buff, &(data->the_array[*i][*j]), ft_strlen(buff)))
	{
		//expander here_doc(data, ...)
		ft_printf(doc, "%s\n", buff);
		free(buff);
		buff = readline(">");
		if (!buff)
			ft_crash(data);
	}
	if (data->exec[idx].infile > 2)
		close(data->exec[idx].infile);
	data->exec[idx].infile = doc;
}

void	parse_infile(t_data *data, int idx, int *i, int *j)
{
	int	fd;

	file_param(data, i, j);
	fd = open(&(data->the_array[*i][*j]), O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(&(data->the_array[*i][*j]));
		return ; //a voir + printf
	}
	if (data->exec[idx].infile > 2)
		close(data->exec[idx].infile);
	data->exec[idx].infile = fd;
}

void	parse_in(t_data *data, int idx, int *i, int *j)
{
	if (data->the_array[*i][*j + 1] == '<')
	{
		(*j)++;
		parse_heredoc(data, idx, i, j);
	}
	else
		parse_infile(data, idx, i, j);
}

void	parse_append(t_data *data, int idx, int *i, int *j)
{
	int	fd;

	file_param(data, i, j);
	fd = open(&(data->the_array[*i][*j]), O_WRONLY | O_CREAT | O_APPEND, 00777);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(&(data->the_array[*i][*j]));
		return ; //a voir + printf
	}
	if (data->exec[idx].outfile > 2)
		close(data->exec[idx].outfile);
	data->exec[idx].outfile = fd;
}

void	parse_outfile(t_data *data, int idx, int *i, int *j)
{
	int	fd;

	file_param(data, i, j);
	fd = open(&(data->the_array[*i][*j]), O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(&(data->the_array[*i][*j]));
		return ; //a voir + printf
	}
	if (data->exec[idx].outfile > 2)
		close(data->exec[idx].outfile);
	data->exec[idx].outfile = fd;
}

void	parse_out(t_data *data, int idx, int *i, int *j)
{
	if (data->the_array[*i][*j + 1] == '>')
	{
		(*j)++;
		parse_append(data, idx, i, j);
	}
	else
		parse_outfile(data, idx, i, j);
}

int	parse_argv(t_data *data, int idx, int *i, int *j)
{
	int		old_j;
	char	*tmp;
	char	**tmp_array;

	old_j = *j;
	while (data->the_array[*i][*j])
	{
		if (data->the_array[*i][*j] == '<' || data->the_array[*i][*j] == '>')
			break ;
		(*j)++;
	}
	tmp = ft_substr(data->the_array[*i], old_j, *j - old_j);
	if (!tmp)
		ft_crash(data);
	if (!data->exec[idx].argv)
		data->exec[idx].argv = ft_calloc(1, sizeof(char *));
	tmp_array = ft_arrayjoin(data->exec[idx].argv, &tmp, 1);
	if (!tmp_array)
	{
		free(tmp);
		ft_crash(data);
	}
	free(data->exec[idx].argv);
	data->exec[idx].argv = tmp_array;
	return (0);
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
			else if (data->the_array[i][j] == '>')
				parse_out(data, idx, &i, &j);
			else
				parse_argv(data, idx, &i, &j);
		}
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
		create_the_array(data, &list);

		int i = 0;
		ft_printf(1, "exec %i\n", exec_idx);
		while (data->the_array[i])
			ft_printf(1, "string '%s'\n", data->the_array[i++]);


		fill_exec(data, exec_idx);
		ft_free_strs(data->the_array, 0, 2);
		data->the_array = NULL;
		exec_idx++;
		if (list)
			list = list->next;
	}
	int	i = 0;
	while(data->exec[i].argv)
	{
		printf("Command %i:\ninfile:%i\noutfile:%i\nargv[0]:%s\n", i, data->exec[i].infile, data->exec[i].outfile, data->exec[i].argv[0]);
		i++;
	}
	free(data->exec);
	data->exec = NULL;
	data->the_array = NULL;
}
