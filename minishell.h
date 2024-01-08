/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:27:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/08 14:26:04 by vilibert         ###   ########.fr       */
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

typedef struct s_lexed {
	char			*word;
	int				token;
	struct s_lexed	*next;
	struct s_lexed	*prev;
}	t_lexed;

# define WORD 0
# define DQUOTE 1
# define SQUOTE 2
# define PIPE 3

void	get_env(char **env, t_data *data);
int		ft_env(t_data *data);
int		ft_cd(t_data *data, char *path_dir);
int		ft_pwd(void);
int		prompt_reader(t_data *data);
char	*get_env_var(char **env, char *var);
void	ft_exit_prog(t_data *data);
void	ft_crash(t_data *data);

t_env	*array_to_struct(t_data *data);
char	**struct_to_array(t_env *env);
int		ft_strslen(char **strs);


t_lexed	*lexer(t_data *data, char **line);
void	ft_free_lexed(t_lexed **list);
void	expand(t_data *data, t_lexed *list);
#endif