/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:04:07 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/16 18:15:28 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	parse_ioa(t_data *data, int idx, t_lexed *list)
{
	int	fd;

	fd = -1;
	if (list->token == INFILE)
		fd = open(list->word, O_RDONLY);
	else if (list->token == OUTFILE)
		fd = open(list->word, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	else if (list->token == APPEND)
		fd = open(list->word, O_WRONLY | O_CREAT | O_APPEND, 00777);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(list->word);
		return ; //a voir + printf
	}
	if (list->token == INFILE && data->exec[idx].infile > 2)
		close(data->exec[idx].infile);
	else if (data->exec[idx].outfile > 2)
		close(data->exec[idx].outfile);
	if (list->token == INFILE)
		data->exec[idx].infile = fd;
	else
		data->exec[idx].outfile = fd;
}

void	create_the_array(t_data *data, t_lexed **list, int exec_idx)
{
	data->the_array = ft_calloc(1, sizeof(char *));
	while ((*list) && (*list)->token != PIPE)
	{
		if ((*list)->token == INFILE || (*list)->token == OUTFILE || (*list)->token == APPEND)
			parse_ioa(data, exec_idx, (*list));
		else if ((*list)->token == HERE_DOC)
			parse_heredoc(data, exec_idx, (*list));
		else if ((*list)->token == WORD)
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
// void	file_param(t_data *data, int *i, int *j)
// {
// 	if (!data->the_array[*i][*j + 1])
// 	{
// 		(*i)++;
// 		*j = 0;
// 	}
// 	else if (data->the_array[*i][*j + 1])
// 		(*j)++;
// 	if (!data->the_array[*i] || !data->the_array[*i][*j])
// 		ft_crash(data);
// }



// void	parse_infile(t_data *data, int idx, int *i, int *j)
// {
// 	int	fd;

// 	file_param(data, i, j);
// 	fd = open(&(data->the_array[*i][*j]), O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_printf(2, "minishell: ");
// 		perror(&(data->the_array[*i][*j]));
// 		return ; //a voir + printf
// 	}
// 	if (data->exec[idx].infile > 2)
// 		close(data->exec[idx].infile);
// 	data->exec[idx].infile = fd;
// }

// void	parse_in(t_data *data, int idx, int *i, int *j)
// {
	
// 		parse_infile(data, idx, i, j);
// }

// void	parse_append(t_data *data, int idx, int *i, int *j)
// {
// 	int	fd;

// 	file_param(data, i, j);
// 	fd = open(&(data->the_array[*i][*j]), O_WRONLY | O_CREAT | O_APPEND, 00777);
// 	if (fd == -1)
// 	{
// 		ft_printf(2, "minishell: ");
// 		perror(&(data->the_array[*i][*j]));
// 		return ; //a voir + printf
// 	}
// 	if (data->exec[idx].outfile > 2)
// 		close(data->exec[idx].outfile);
// 	data->exec[idx].outfile = fd;
// }

// void	parse_outfile(t_data *data, int idx, int *i, int *j)
// {
// 	int	fd;

// 	file_param(data, i, j);
// 	fd = open(&(data->the_array[*i][*j]), O_WRONLY | O_CREAT | O_TRUNC, 00777);
// 	if (fd == -1)
// 	{
// 		ft_printf(2, "minishell: ");
// 		perror(&(data->the_array[*i][*j]));
// 		return ; //a voir + printf
// 	}
// 	if (data->exec[idx].outfile > 2)
// 		close(data->exec[idx].outfile);
// 	data->exec[idx].outfile = fd;
// }

// void	parse_out(t_data *data, int idx, int *i, int *j)
// {
// 	if (data->the_array[*i][*j + 1] == '>')
// 	{
// 		(*j)++;
// 		parse_append(data, idx, i, j);
// 	}
// 	else
// 		parse_outfile(data, idx, i, j);
// }

// int	parse_argv(t_data *data, int idx, int *i, int *j)
// {
// 	int		old_j;
// 	char	*tmp;
// 	char	**tmp_array;

// 	old_j = *j;
// 	while (data->the_array[*i][*j])
// 	{
// 		if (data->the_array[*i][*j] == '<' || data->the_array[*i][*j] == '>')
// 			break ;
// 		(*j)++;
// 	}
// 	tmp = ft_substr(data->the_array[*i], old_j, *j - old_j);
// 	if (!tmp)
// 		ft_crash(data);
// 	if (!data->exec[idx].argv)
// 		data->exec[idx].argv = ft_calloc(1, sizeof(char *));
// 	tmp_array = ft_arrayjoin(data->exec[idx].argv, &tmp, 1);
// 	if (!tmp_array)
// 	{
// 		free(tmp);
// 		ft_crash(data);
// 	}
// 	free(data->exec[idx].argv);
// 	data->exec[idx].argv = tmp_array;
// 	return (0);
// }

// void	fill_exec(t_data *data, int idx)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (data->the_array[i])
// 	{
// 		j = 0;
// 		while (data->the_array[i][j])
// 		{
// 			if (data->the_array[i][j] == '<')
// 				parse_in(data, idx, &i, &j);
// 			else if (data->the_array[i][j] == '>')
// 				parse_out(data, idx, &i, &j);
// 			else
// 				parse_argv(data, idx, &i, &j);
// 		}
// 		i++;
// 	}
// }

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
		if (list)
			list = list->next;
	}
	// int	i = 0;
	// while(data->exec[i].argv)
	// {
	// 	printf("Command %i:\ninfile:%i\noutfile:%i\nargv[0]:%s\n", i, data->exec[i].infile, data->exec[i].outfile, data->exec[i].argv[0]);
	// 	i++;
	// }
	data->the_array = NULL;
}
