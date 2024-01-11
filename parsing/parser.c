/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:04:07 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/11 19:10:55 by jgoudema         ###   ########.fr       */
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

void	clear_crash(t_data *data, char **the_array)
{
	ft_free_strs(the_array, 0, 2);
	ft_crash(data);
}

char	**join(t_data *data, char **the_array, char ***w_split, int *i)
{
	char	*tmp;

	(void) data;
	*i = ft_strslen(the_array) - 1;
	tmp = ft_strjoin(the_array[*i], *w_split[0]);
	if (!tmp)
	{
		ft_free_strs(*w_split, 0, 2);
		clear_crash(data, the_array);
	}
	free(*w_split[0]);
	free(the_array[*i]);
	the_array[*i] = tmp;
	(*w_split)++;
	return (the_array);
}

char	**create_the_array_word(t_data *data, t_lexed **list, char **the_array)
{
	char	**w_split;
	char	**tmp_array;
	int		i;

	w_split = ft_split((*list)->word, ' ');
	i = -10;
	if (!w_split)
		clear_crash(data, the_array);
	if ((*list)->prev && (*list)->prev->token != PIPE 
		&& (*list)->word[0] != ' ')
		the_array = join(data, the_array, &w_split, &i);
	tmp_array = ft_arrayjoin(the_array, w_split, ft_strslen(w_split));
	if (!tmp_array)
	{
		ft_free_strs(w_split, 0, 2);
		clear_crash(data, the_array);
	}
	free(the_array);
	if (i != -10)
		w_split--;
	free(w_split);
	return (tmp_array);
}

char	**create_the_array_quot(t_data *data, t_lexed **list, char **the_array)
{
	char	*tmp;
	char	**tmp_array;

	if (((*list)->prev && (*list)->prev->token == WORD 
			&& (*list)->prev->word[ft_strlen((*list)->prev->word) - 1] == ' ')
		|| !(*list)->prev)
	{
		tmp = ft_strdup((*list)->word);
		tmp_array = ft_arrayjoin(the_array, &tmp, 1);
		free(the_array);
		return (tmp_array);
	}
	else
	{
		tmp = ft_strjoin(the_array[ft_strslen(the_array) - 1], (*list)->word);
		free(the_array[ft_strslen(the_array) - 1]);
		if (!tmp)
			clear_crash(data, the_array);
		the_array[ft_strslen(the_array) - 1] = tmp;
		tmp_array = the_array;
	}
	return (tmp_array);
}

char	**create_the_array(t_data *data, t_lexed **list)
{
	char	**the_array;

	the_array = ft_calloc(1, sizeof(char *));
	while ((*list) && (*list)->token != PIPE)
	{
		if ((*list)->token == WORD)
			the_array = create_the_array_word(data, list, the_array);
		else if ((*list)->token == DQUOTE || (*list)->token == SQUOTE)
			the_array = create_the_array_quot(data, list, the_array);
		*list = (*list)->next;
	}
	// int i=0;
	// while(the_array[i])
	// 	ft_printf(1, "%s\n", the_array[i++]);
	return (the_array);
}

void	parse(t_data *data)
{
	int		exec_idx;
	char	**the_array;
	t_lexed	*list;

	list = data->list;
	if (!list)
		return ;
	data->exec = malloc(tab_size(list) * sizeof(t_exec));
	if (!data->exec)
		ft_crash(data);
	exec_idx = 0;
	while (exec_idx < 1)
	{
		the_array = create_the_array(data, &list);
		
		// remplir exec
		exec_idx++;
	}
	free(data->exec);
	ft_free_strs(the_array, 0, 2);
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
