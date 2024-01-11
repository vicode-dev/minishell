/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:26:17 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/11 13:46:20 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned char	g_exitcode;



static int	expand_exit_code(t_data *data, t_lexed *list, int i)
{
	char	*tmp;
	int		len;

	tmp = ft_itoa((int)g_exitcode);
	len = ft_strlen(tmp);
	tmp = ft_replace(list->word, tmp, i, i + 2);
	if (!tmp)
		ft_crash(data);
	free(list->word);
	list->word = tmp;
	return (len);
}

static int	expand_env_var(t_data *data, t_lexed *list, int i)
{
	int		j;
	char	*new;
	char	*tmp;

	j = i + 1;
	while (list->word[j] && list->word[j] != ' ' && list->word[j] != '$')
		j++;
	new = ft_substr(list->word, i, j - i);
	if (!new)
		ft_crash(data);
	tmp = get_env_var(data->env, new + 1);
	free(new);
	new = ft_replace(list->word, tmp, i, j);
	if (!new)
		ft_crash(data);
	free(list->word);
	list->word = new;
	return (ft_strlen(tmp));
}

static int	expand_home(t_data *data, t_lexed *list, int i)
{
	char	*home;
	char	*tmp;

	home = get_env_var(data->env, "HOME");
	tmp = ft_replace(list->word, ft_strdup(home), i, i + 1);
	if (!tmp)
		ft_crash(data);
	free(list->word);
	list->word = tmp;
	return (ft_strlen(home));
}

static void	expand(t_data *data, t_lexed *list)
{
	int		i;

	i = 0;
	while (list->word[i])
	{
		if (list->token == WORD && list->word[i] == '~')
			i += expand_home(data, list, i);
		else if (list->word[i] == '$' && list->word[i + 1] == '?')
			i += expand_exit_code(data, list, i);
		else if (list->word[i] == '$' && 
			(list->word[i + 1] == ' ' || list->word[i + 1] == 0))
			i++;
		else if (list->word[i] == '$')
			i += expand_env_var(data, list, i);
		else
			i++;
	}
}

void	expander(t_data *data)
{
	t_lexed	*tmp;

	tmp = data->list;
	while (tmp)
	{
		if (tmp->token == WORD || tmp->token == DQUOTE)
			expand(data, tmp);
		tmp = tmp->next;
	}
}