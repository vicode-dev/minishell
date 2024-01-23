/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:05:38 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 17:31:37 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_syntax_error(t_data *data, char c)
{
	if (!c)
		ft_printf(2, 
			"minishell: syntax error near unexpected token `newline'\n");
	else
		ft_printf(2, "minishell: syntax error near unexpected token `%c'\n", c);
	data->status = SYNTAX_ERROR;
}

void	syntax_find(char *str, int *i, int *cmd)
{
	if (str[*i] == '<' || str[*i] == '>')
	{
		*cmd = 0;
		if (str[*i] == '<')
		{
			if (str[*i + 1] == '<')
				(*i)++;
		}
		if (str[*i] == '>')
		{
			if (str[*i + 1] == '>')
				(*i)++;
		}
		(*i)++;
	}
}

void	syntax_quotes(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
}

int	check_syntax_error(t_data *data, char *str)
{
	int	cmd;
	int	i;

	i = 0;
	cmd = 1;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		syntax_find(str, &i, &cmd);
		while (str[i] == ' ')
			i++;
		if (str[i] == '"')
			syntax_quotes(str, &i, '"');
		else if (str[i] == '\'')
			syntax_quotes(str, &i, '\'');
		else if ((!cmd && str[i] == '|') || str[i] == '<'
			|| str[i] == '>' || !str[i])
			return (print_syntax_error(data, str[i]), 1);
		if (str[i])
			i++;
	}
	return (0);
}

int	syntax_checker(t_data *data, t_lexed *list)
{
	if (list && list->token == PIPE)
		return (print_syntax_error(data, '|'), 1);
	while (list && list->next)
	{
		if (list->token == PIPE && list->next->token == PIPE)
			return (print_syntax_error(data, '|'), 1);
		list = list->next;
	}
	if (list->token == PIPE)
		return (print_syntax_error(data, '|'), 1);
	return (0);
}
