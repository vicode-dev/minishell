/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:27:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/09 16:43:31 by vilibert         ###   ########.fr       */
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
	t_exec	*exec;
}	t_data;

typedef struct s_lexed {
	char			*word;
	int				token;
	struct s_lexed	*next;
	struct s_lexed	*prev;
}	t_lexed;

typedef struct s_exec{
	int		infile;
	int		outfile;
	char	*path;
	char	**argv;
}	t_exec;

# define WORD 0
# define DQUOTE 1
# define SQUOTE 2
# define PIPE 3

// Export
int		ft_export(t_data *data, char **vars, int *in_out);
void	export_parse(t_data *data, char **vars, int *in_out);
void	export_add(t_data *data, char *arg, int out);

void	get_env(char **env, t_data *data);
int		ft_env(t_data *data, int out);
int		ft_cd(t_data *data, char *path_dir);
int		ft_pwd(void);
int		ft_structlen(t_env *env);
int		prompt_reader(t_data *data);
char	*get_env_var(char **env, char *var);
void	ft_exit_prog(t_data *data);
void	ft_crash(t_data *data);

t_env	*array_to_struct(t_data *data);
char	**struct_to_array(t_env *env);
int		ft_strslen(char **strs);

// Parsing
t_lexed	*lexer(t_data *data, char **line);
void	ft_free_lexed(t_lexed **list);
void	expander(t_data *data, t_lexed *list);
t_exec	*parse(t_data *data, t_lexed *list);
#endif