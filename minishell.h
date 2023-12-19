/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:27:48 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/19 17:35:54 by vilibert         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

typedef struct s_env
{
	char	*name;
	char	*content;
}	t_env;

typedef struct s_data {
	char	**env;
	char	**var;
}	t_data;

void	get_env(char **env, t_data *data);
int		ft_env(t_data *data);
int		ft_cd(t_data *data, char *path_dir);
int		ft_pwd(void);
int		prompt_reader(t_data *data);
char	*get_env_var(char **env, char *var);
void	ft_exit_prog(t_data *data);
void	ft_crash(t_data *data);

#endif