/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:26:17 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/09 12:13:44 by vilibert         ###   ########.fr       */
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
	if (!new_str)
	{
		tmp = ft_strjoin(part_1, part_2);
		return (free(part_1), free(part_2), tmp);
	}
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
int		expand_env_var(t_data *data, t_lexed *list, int i)
{
	int		j;
	char	*new;
	char	*tmp;

	j = i + 1;
	while (list->word[j] && list->word[j] != ' ' && list->word[j] != '$')
		j++;
	new = ft_substr(list->word, i, j - i);
	if (!new)
	{
		ft_free_lexed(&list);
		ft_crash(data);
	}
	tmp = get_env_var(data->env, new + 1);
	free(new);
	new = ft_replace(list->word, tmp, i, j);
	if (!new)
	{
		ft_free_lexed(&list);
		ft_crash(data);
	}
	free(list->word);
	list->word = new;
	if (tmp)
		return (ft_strlen(tmp));
	return (0);
}
int	expand_home(t_data *data, t_lexed *list, int i)
{
	char	*home;
	char	*tmp;

	home = get_env_var(data->env, "HOME");
	tmp = ft_replace(list->word, ft_strdup(home), i, i + 1);
	if (!tmp)
	{
		ft_free_lexed(&list);
		ft_crash(data);
	}
	free(list->word);
	list->word = tmp;
	return (ft_strlen(home));
}

void	expand(t_data *data, t_lexed *list)
{
	int		i;
	
	i = 0;
	while (list->word[i])
	{
		if (list->token == WORD && list->word[i] == '~')
			i += expand_home(data, list, i);
		else if (list->word[i] == '$' && 
			(list->word[i + 1] == ' ' || list->word[i + 1] == 0))
			i++;
		else if (list->word[i] == '$')
			i += expand_env_var(data, list, i);
		else
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