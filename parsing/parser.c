/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:04:07 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/10 19:58:58 by vilibert         ###   ########.fr       */
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

char	**create_the_array(t_data *data, t_lexed **list) //creer char**: ['ls<out', 'ls', -la, 'a b']
{
	char	**temp;
	char	**the_array;
	char	**temp2;
	char	*str;

	(void) data;
	the_array = ft_calloc(1, sizeof(char *));
	while ((*list) && (*list)->token != PIPE)
	{
		if ((*list)->token == WORD)
		{
			temp = ft_split((*list)->word, ' ');
			if ((*list)->prev && (*list)->prev->token != PIPE)
			{
				str = ft_strjoin(the_array[ft_strslen(the_array) - 1], temp[0]);
				free(temp[0]);
				free(the_array[ft_strslen(the_array) - 1]);
				the_array[ft_strslen(the_array) - 1] = str;
				temp++;
			}
			temp2 = ft_arrayjoin(the_array, temp, ft_strslen(temp));
			free(the_array);
			free(temp);
			the_array = temp2;
		}
		// if ((*list)->token == DQUOTE || (*list)->token == SQUOTE)
			// if prec espace-> arrayjoin | pas espace -> join
		*list = (*list)->next;
	}

	int i=0;
	while(the_array[i])
		ft_printf(1, "%i %s\n", i, the_array[i++]);

	return (the_array);
}

void	parse(t_data *data, t_lexed *list)
{
	int	exec_idx;
	char	**the_array;
	// int	j;
	if (!list)
		return ;
	data->exec = malloc(tab_size(list) * sizeof(t_exec));
	if (!data->exec)
	{
		ft_free_lexed(&list);
		ft_crash(data);
	}
	exec_idx = 0;
	
	while (exec_idx < 1)
	{
		the_array = create_the_array(data, &list);
		// remplir exec
		exec_idx++;
	}
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
