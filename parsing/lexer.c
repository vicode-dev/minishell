/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:25:57 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/10 12:23:46 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lexed(t_lexed **list)
{
	t_lexed	*tmp;

	while (*list && (*list)->prev)
		*list = (*list)->prev;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->word);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

int	lst_add(t_lexed **list, int token, char *word)
{
	t_lexed	*new;

	if (!word && (token != PIPE))
		return (ft_free_lexed(list), 1);
	new = malloc(sizeof(t_lexed));
	if (!new)
		return (ft_free_lexed(list), free(word), 1);
	new->next = NULL;
	new->prev = NULL;
	new->token = token;
	new->word = word;
	if (!*list)
	{
		(*list) = new;
		return (0);
	}
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new;
	new->prev = (*list);
	while ((*list)->prev)
		(*list) = (*list)->prev;
	return (0);
}

int	get_end_quot(char **line, int i, char type)
{
	char	*tmp;
	char	*new_line;

	while (!ft_strchr(*line + i, type))
	{
		tmp = readline("quote>");
		if (!tmp)
			return (1);
		new_line = ft_strjoin(*line, "\n");
		if (!new_line)
			return (1);
		free(*line);
		*line = ft_strjoin(new_line, tmp);
		free(tmp);
		free(new_line);
		if (!*line)
			return (1);
	}
	return (0);
}

int	get_quot(t_lexed **list, char **line, int *i)
{
	char	type;
	int		i_cpy;
	int		j;

	type = (*line)[*i];
	i_cpy = *i + 1;
	if (!ft_strchr((*line) + i_cpy, type) && get_end_quot(line, i_cpy, type))
		return (ft_free_lexed(list), 1);
	j = i_cpy;
	while ((*line)[j])
	{
		if ((*line)[j] == type)
		{
			*i += j - i_cpy + 1; 
			if (type == '"')
				return (lst_add(list, DQUOTE,
						ft_substr(*line, i_cpy, j - i_cpy)));
			if (type == '\'')
				return (lst_add(list, SQUOTE,
						ft_substr(*line, i_cpy, j - i_cpy)));
		}
		j++;
	}
	return (1);
}

int	get_word(t_lexed **list, char *line, int *i)
{
	int	j;

	j = *i;
	while (line[*i] && line[*i] != '"' && line[*i] != '\'' && line[*i] != '|')
		(*i)++;
	(*i)--;
	return (lst_add(list, WORD, ft_substr(line, j, *i + 1 - j)));
}

t_lexed	*lexer(t_data *data, char **line)
{
	int		i;
	t_lexed	*list;

	i = 0;
	list = NULL;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == '"' || (*line)[i] == '\'')
		{
			if (get_quot(&list, line, &i))
				ft_crash(data);
		}
		else if ((*line)[i] == '|')
		{
			if (lst_add(&list, PIPE, NULL))
				ft_crash(data);
		}
		else if (get_word(&list, *line, &i))
			ft_crash(data);
		i++;
	}
	return (list);
}
