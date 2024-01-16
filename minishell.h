/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:27:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/16 18:14:01 by jgoudema         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_env
{
	char	*name;
	char	*content;
}	t_env;

typedef struct s_exec {
	int		infile;
	int		outfile;
	char	*path;
	char	**argv;
}	t_exec;

typedef struct s_lexed {
	char			*word;
	int				token;
	struct s_lexed	*next;
	struct s_lexed	*prev;
}	t_lexed;

typedef struct s_data {
	char	**env;
	char	**the_array;
	int		status;
	int		pid;
	t_exec	*exec;
	t_lexed	*list;
}	t_data;

# define WORD 0
# define DQUOTE 1
# define SQUOTE 2
# define PIPE 3
# define HERE_DOC 4
# define INFILE 5
# define OUTFILE 6
# define APPEND 7

// Export
int		ft_export(t_data *data, char **vars, int out);
int		export_parse(t_data *data, char *var, int out);
int		export_add(t_data *data, char *arg);
int		export_replace(t_data *data, char *arg, int pos, int i);
int		print_env(t_data *data, int out);
int		ft_strcmp(char *s1, char *s2);
int		check_existence(t_data *data, char *var, int i);

void	get_env(char **env, t_data *data);
int		ft_env(t_data *data, int out);
int		ft_unset(t_data *data, char **arg);
int		ft_cd(t_data *data, char *path_dir);
int		ft_echo(t_data *data, char **args, int out);
int		ft_pwd(void);
int		ft_structlen(t_env *env);
int		prompt_reader(t_data *data);
char	*get_env_var(char **env, char *var);
void	ft_exit_prog(t_data *data);
void	ft_crash(t_data *data);
void	ft_free_strs(char **board, int i, int quit);

t_env	*array_to_struct(t_data *data);
char	**struct_to_array(t_env *env);

// Parsing
t_lexed	*lexer(t_data *data, char **line);
char	*get_quot(char **line, int *i);
char	*get_token(char **line, int *i, int token);
void	ft_free_lexed(t_lexed **list);
void	expander(t_data *data);
void	parse(t_data *data);
int		get_end_quot(char **line, int i, char type);
void	parse_heredoc(t_data *data, int idx, t_lexed *list);
int		tab_size(t_lexed *list);
void	create_the_array_word(t_data *data, t_lexed **list);
void	create_the_array_quot(t_data *data, t_lexed **list);

// Execution
int		executer(t_data *data);
void	ft_init_pipex(t_data *data, int i);

#endif