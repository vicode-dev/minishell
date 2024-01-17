/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:00:39 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/17 10:28:09 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_quot(char **line, int *i)
{
	char	type;
	int		i_cpy;
	int		j;

	type = (*line)[*i];
	i_cpy = *i + 1;
	if (!ft_strchr((*line) + i_cpy, type) && get_end_quot(line, i_cpy, type))
		return (NULL);
	j = i_cpy;
	while ((*line)[j])
	{
		if ((*line)[j] == type)
		{
			*i += j - i_cpy + 1; 
			if (type == '"')
				return (ft_substr(*line, i_cpy, j - i_cpy));
			if (type == '\'')
				return (ft_substr(*line, i_cpy, j - i_cpy));
		}
		j++;
	}
	return (NULL);
}