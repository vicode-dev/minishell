/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:59:50 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/29 11:28:04 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	syntax_quotes(char *str, int *i, int *cmd)
{
	if (str[*i] == '"')
	{
		*cmd = 1;
		(*i)++;
		while (str[*i] && str[*i] != '"')
			(*i)++;
	}
	if (str[*i] == '\'')
	{
		*cmd = 1;
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
}

static void	syntax_cmd(char *str, int *i, int *cmd)
{
	while (str[*i] && str[*i] != '>' && str[*i] != '<')
	{
		syntax_quotes(str, i, cmd);
		if (str[*i] == '|' && !(*cmd))
			return ;
		if (str[*i] != ' ')
			*cmd = 1;
		if (str[*i])
			(*i)++;
	}
}

static void	syntax_find(char *str, int *i, int *cmd)
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
		syntax_cmd(str, i, cmd);
	}
}

int	check_syntax_error(t_data *data, char *str)
{
	int	cmd;
	int	i;

	i = 0;
	cmd = 1;
	while (str[i])
	{
		syntax_quotes(str, &i, &cmd);
		syntax_find(str, &i, &cmd);
		if (!cmd)
			return (print_syntax_error(data, str[i]), 1);
		if (str[i])
			i++;
	}
	return (0);
}
