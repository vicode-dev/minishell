/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:27:48 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/24 14:06:09 by vilibert         ###   ########.fr       */
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
# include <errno.h>
# include <term.h>
# include "libft/libft.h"
# include "exitcode.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

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
	char	*line;
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

// BUILTINS - Export, unset
void	ft_export(t_data *data, char **vars);
int		export_parse(t_data *data, char *var);
int		export_add(t_data *data, char *arg);
int		export_replace(t_data *data, char *arg, int pos, int i);
int		print_env(t_data *data);
int		ft_strcmp(char *s1, char *s2);
int		check_existence(t_data *data, char *var, int i);
void	ft_unset(t_data *data, char **arg);
void	ft_cd(t_data *data, char **argv);

// BUILTINS - Env
void	get_env(char **env, t_data *data);
void	ft_env(t_data *data);

// BUILTINS - Cd, echo, pwd, exit
void	ft_cd(t_data *data, char *argv[0]);
void	ft_echo(t_data *data, char **argv);
void	ft_pwd(t_data *data);
void	ft_exit(t_data *data, char **argv);

int		ft_structlen(t_env *env);
int		prompt_reader(t_data *data);
char	*get_env_var(char **env, char *var);
t_env	*array_to_struct(t_data *data);
void	free_struct_env(t_env *env);

// PARSING
int		check_syntax_error(t_data *data, char *str);
void	print_syntax_error(t_data *data, char c);
void	lexer(t_data *data, char **line);
char	*get_quot(char **line, int *i);
char	*get_token(char **line, int *i, int token);
void	expander(t_data *data);
void	parse(t_data *data);
int		get_end_quot(char **line, int i, char type);
void	here_doc(t_data *data, int idx, t_lexed *list);
char	*expand(t_data *data, char *buff);
int		tab_size(t_lexed *list);
void	create_the_array_word(t_data *data, t_lexed **list);
void	create_the_array_quot(t_data *data, t_lexed **list);
int		syntax_checker(t_data *data, t_lexed *list);

// EXECUTION
void	executer(t_data *data);
void	ft_init_pipex(t_data *data, int i, int stdout_cpy);
void	exec_builtins(t_data *data, int type, int i);
int		is_builtins(char *str);
char	*get_path(t_data *data, char *cmd, char **env);
void	redirect_exec_builtins(t_data *data, int type, int i);
int		is_directory(const char *path);

// FREE
void	ft_free_cycle(t_data *data);
void	ft_free_lexed(t_lexed **list);
void	ft_exit_prog(t_data *data);
void	ft_crash(t_data *data);
void	ft_free_strs(char **board, int i, int quit);

//Signals
void	enable_signal_print(void);
void	disable_signal_print(void);
void	sig_interrupt(int signal);
void	sig_interrupt_exec(int signal);
void	sig_quit(int signal);

//Protos
void	rl_clear_history(void);
void	rl_replace_line(const char *str, int undo);

#endif