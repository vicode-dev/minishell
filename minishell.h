/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:27:48 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/18 17:48:18 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include "libft/libft.h"


typedef struct s_data {
	char	**env;
	char	**var;
}	t_data;

void	get_env(char **env, t_data *data);
int		ft_env(t_data *data);
int		ft_cd(t_data *data, char *path_dir);

#endif