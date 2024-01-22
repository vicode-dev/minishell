/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:05:38 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/22 18:15:26 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_syntax_error(t_data *data)
{
	ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
	data->status = SYNTAX_ERROR;
}

int	syntax_checker(t_data *data, t_lexed *list)
{
	if (list && list->token == PIPE)
		return (print_syntax_error(data), 1);
	while (list && list->next)
	{
		if (list->token == PIPE && list->next->token == PIPE)
			return (print_syntax_error(data), 1);
		list = list->next;
	}
	if (list->token == PIPE)
		return (print_syntax_error(data), 1);
	return (0);
}
