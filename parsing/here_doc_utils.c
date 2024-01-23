/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:56:23 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 16:58:29 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_exit_code(t_data *data, char *buff, int i)
{
	char	*tmp;
	int		len;

	tmp = ft_itoa(data->status);
	len = ft_strlen(tmp);
	tmp = ft_replace(buff, tmp, i, i + 2);
	free(buff);
	if (!tmp)
		ft_crash(data);
	buff = tmp;
	return (buff);
}

static char	*expand_env_var(t_data *data, char *buff, int i)
{
	int		j;
	char	*new;
	char	*tmp;

	j = i + 1;
	while (buff[j] && (ft_isalnum(buff[j]) || buff[j] == '_'))
		j++;
	new = ft_substr(buff, i, j - i);
	if (!new)
		ft_crash(data);
	tmp = get_env_var(data->env, new + 1);
	free(new);
	new = ft_replace(buff, tmp, i, j);
	free(buff);
	if (!new)
		ft_crash(data);
	buff = new;
	return (buff);
}

char	*expand(t_data *data, char *buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '$' && buff[i + 1] == '?')
			buff = expand_exit_code(data, buff, i);
		else if (buff[i] == '$' && 
			(!ft_isalnum(buff[i + 1]) || buff[i + 1] == 0))
			i++;
		else if (buff[i] == '$')
			buff = expand_env_var(data, buff, i);
		else
			i++;
	}
	return (buff);
}
