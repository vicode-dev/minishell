/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_temp.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:27:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/19 09:56:01 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TEMP_H
# define MINISHELL_TEMP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char	*name;
	char	*content;
}	t_env;

typedef struct s_data {
	t_env	*env;
	char	**var;
}	t_data;

void	get_env(char **env, t_data *data);
int		ft_env(t_data *data);
int		ft_cd(t_data *data, char *argv[0]);
int		ft_pwd(t_data *data);
char	**struct_to_array(t_data *data);

#endif
