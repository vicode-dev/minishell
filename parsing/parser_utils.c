/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:02:56 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 15:22:43 by vilibert         ###   ########.fr       */
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
	if ((*list)->prev && ((*list)->prev->token == DQUOTE
			|| (*list)->prev->token == SQUOTE)
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
