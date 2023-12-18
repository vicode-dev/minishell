/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:28:18 by vicode            #+#    #+#             */
/*   Updated: 2023/12/05 19:18:40 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **bye)
{
	int	i;

	i = 0;
	if (!bye)
		return (NULL);
	while (bye[i])
	{
		free(bye[i]);
		i++;
	}
	free(bye);
	return (NULL);
}

static size_t	ft_count_strings(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == sep))
			i++;
		if (str[i])
			count++;
		while (str[i] && !(str[i] == sep))
			i++;
	}
	return (count);
}

static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == c)
			return ;
		(*next_word_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*nxtword;
	size_t	nxtwordl;
	size_t	i;

	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (ft_count_strings(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	nxtword = (char *)s;
	nxtwordl = 0;
	while (i < ft_count_strings(s, c))
	{
		ft_get_next_word(&nxtword, &nxtwordl, c);
		res[i] = (char *)malloc(sizeof(char) * (nxtwordl + 1));
		if (!res[i])
			return (ft_free(res));
		ft_strlcpy(res[i], nxtword, nxtwordl + 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}
