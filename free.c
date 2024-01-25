/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:22:05 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/25 11:35:34 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

/**
 * @brief exit the whole minishell with exitcode 1
 * 
 * @param data 
 */
void	ft_crash(t_data *data)
{
	data->status = 1;
	ft_exit_prog(data);
}

/**
 * @brief free a string array
 * 
 * @param board the array to free
 * @param i the first index in array to be freed
 * @param quit 0 or 1 for exit and -1 for doing nothing
 */
void	ft_free_strs(char **board, int i, int quit)
{
	while (board && board[i])
		free(board[i++]);
	free(board);
	if (quit == 1 || quit == 0)
		exit(quit);
}

/**
 * @brief free linked list from the lexer
 * 
 * @param list 
 */
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

/**
 * @brief free and close data except env
 * 
 * @param data 
 */
void	ft_free_cycle(t_data *data)
{
	int	i;

	i = 0;
	if (data->the_array)
		ft_free_strs(data->the_array, 0, 2);
	ft_free_lexed(&(data->list));
	if (data->exec)
	{
		while (data->exec[i].argv)
		{
			ft_free_strs(data->exec[i].argv, 0, 2);
			free(data->exec[i].path);
			if (data->exec[i].infile > 2)
				close(data->exec[i].infile);
			if (data->exec[i].outfile > 2)
				close(data->exec[i].outfile);
			i++;
		}
		free(data->exec);
		data->exec = NULL;
	}
	if (data->line)
		free(data->line);
	data->line = 0;
	g_signal = 0;
}

/**
 * @brief free the whole data struct and exit on data->status
 * 
 * @param data 
 */
void	ft_exit_prog(t_data *data)
{
	ft_free_strs(data->env, 0, 2);
	rl_clear_history();
	ft_free_cycle(data);
	enable_signal_print();
	exit (data->status);
}
