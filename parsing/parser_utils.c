/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:02:56 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/24 10:08:06 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	get_token_handler(char **line, int *i_cpy, int *j, char **res)
{
	char	*tmp;
	char	*tmp_2;

	while ((*line)[*j])
	{
		if ((*line)[*j] == '"' || (*line)[*j] == '\'')
		{
			tmp = ft_substr(*line, *i_cpy, *j - *i_cpy);
			tmp_2 = ft_strjoin(*res, tmp);
			free(tmp);
			free(*res);
			*i_cpy = *j;
			tmp = get_quot(line, i_cpy);
			*res = ft_strjoin(tmp_2, tmp);
			free(tmp_2);
			free(tmp);
			(*i_cpy)++;
			*j = *i_cpy;
		}
		else
			(*j)++;
		if ((*line)[*j] == ' ' || (*line)[*j] == '<' || (*line)[*j] == '>'
			|| (*line)[*j] == '|')
			break ;
	}
}

char	*get_token(char **line, int *i, int token)
{
	int		i_cpy;
	int		j;
	char	*res;
	char	*tmp;
	char	*tmp_2;

	i_cpy = *i;
	if (token == HERE_DOC || token == APPEND)
		i_cpy += 2;
	else
		i_cpy++;
	while ((*line)[i_cpy] == ' ')
		i_cpy++;
	j = i_cpy;
	res = ft_calloc(1, 1);
	get_token_handler(line, &i_cpy, &j, &res);
	tmp = ft_substr(*line, i_cpy, j - i_cpy);
	tmp_2 = ft_strjoin(res, tmp);
	free(tmp);
	free(res);
	*i = j - 1;
	return (tmp_2);
}
