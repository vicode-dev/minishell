/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:26:17 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/22 12:14:30 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_replace(char *old_str, char *new_str, int i, int j)
{
	char	*part_1;
	char	*part_2;
	char	*tmp;

	part_1 = ft_substr(old_str, 0, i);
	part_2 = ft_substr(old_str, j, ft_strlen(old_str + j));
	if (!part_1 || !part_2)
		return (free(part_1), free(part_2), NULL);
	tmp = ft_strjoin(part_1, new_str);
	free(part_1);
	if (!tmp)
		return (free(part_2), NULL);
	part_1 = ft_strjoin(tmp, part_2);
	free(part_2);
	free(tmp);
	if (!part_1)
		return (NULL);
	return (part_1);
}

void	expand(t_data *data, t_lexed *list)
{
	int		i;
	int		j;
	char	*new;
	char	*tmp;

	i = 0;
	while (list->word[i])
	{
		if (list->word[i] == '$')
		{
			j = i;
			while (list->word[j] && list->word[j] != ' ')
				j++;
			new = ft_substr(list->word, i, j - i);
			// if (!new)
				// free_lexed(list);
				// ft_crash(data);
			tmp = get_env_var(data->env, new + 1);
			free(new);
			new = ft_replace(list->word, tmp, i, j);
			if (!new)
			{
				// free_lexed(list);
				ft_crash(data);
			}
			free(list->word);
			list->word = new;
		}
		i++;
	}
}

void	expander(t_data *data, t_lexed *list)
{
	t_lexed	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->token == WORD || tmp->token == DQUOTE)
			expand(data, tmp);
		tmp = tmp->next;
	}
}