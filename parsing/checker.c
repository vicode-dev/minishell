/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:05:38 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 15:31:45 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_syntax_error(t_data *data, char c)
{
	if (!c)
		ft_printf(2, "minishell: syntax error near unexpected token\
		 `newline'\n");
	else
		ft_printf(2, "minishell: syntax error near unexpected token `%c'\n", c);
	data->status = SYNTAX_ERROR;
}

int	check_syntax_error(t_data *data, char *str)
{
	int	cmd;
	int	i;

	i = 0;
	cmd = 0;
	while (str[i])
	{
		// printf("3 : %c\n", str[i]);
		while (str[i] == ' ')
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i] == '<')
			{
				if (str[i + 1] == '<')
					i++;
			}
			if (str[i] == '>')
			{
				if (str[i + 1] == '>')
					i++;
			}
			i++;
		}
		// printf("1 : %c\n", str[i]);
		while (str[i] == ' ')
			i++;
		// printf("2 : %c\n", str[i]);
		if (str[i] == '"')
		{
			cmd = 1;
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		else if (str[i] == '\'')
		{
			cmd = 1;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if ((!cmd && str[i] == '|') || str[i] == '<'
			|| str[i] == '>' || !str[i])
			return (print_syntax_error(data, str[i]), 1);
		if (str[i])
			i++;
		// printf("4 : %c\n", str[i]);
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
