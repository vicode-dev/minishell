/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:25:57 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/16 18:06:48 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	lst_add(t_lexed **list, int token, char *word)
{
	t_lexed	*new;

	if (!word && (token != PIPE))
		return (ft_free_lexed(list), 1);
	new = malloc(sizeof(t_lexed));
	if (!new)
		return (free(word), 1);
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

static char	*get_word(char *line, int *i)
{
	int	j;

	j = *i;
	while (line[*i] && line[*i] != '"' && line[*i] != '\'' && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>')
		(*i)++;
	(*i)--;
	return (ft_substr(line, j, *i + 1 - j));
}

void	lst_add_handler(t_data *data, int token, char *word)
{
	if (lst_add(&(data->list), token, word))
		ft_crash(data);
}

t_lexed	*lexer(t_data *data, char **line)
{
	int		i;

	i = 0;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == '"')
			lst_add_handler(data, DQUOTE, get_quot(line, &i));
		if ((*line)[i] == '\'')
			lst_add_handler(data, SQUOTE, get_quot(line, &i));
		else if ((*line)[i] == '|')
			lst_add_handler(data, PIPE, NULL);
		else if ((*line)[i] == '<' && (*line)[i + 1] == '<')
			lst_add_handler(data, HERE_DOC, get_token(line, &i, HERE_DOC));
		else if ((*line)[i] == '<')
			lst_add_handler(data, INFILE, get_token(line, &i, INFILE));
		else if ((*line)[i] == '>' && (*line)[i + 1] == '>')
			lst_add_handler(data, APPEND, get_token(line, &i, APPEND));
		else if ((*line)[i] == '>')
			lst_add_handler(data, OUTFILE, get_token(line, &i, OUTFILE));
		else
			lst_add_handler(data, WORD, get_word(*line, &i));
		i++;
	}
	return (data->list);
}
