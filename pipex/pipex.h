/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:47:35 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/11 15:39:44 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		f1;
	int		f2;
	char	**cmds;
	char	***args;
	int		count;
	int		here_doc;
	int		status;
	int		pid;
}	t_data;

t_data	ft_init_data(int argc, char **argv);
void	ft_parse(t_data *data, char **argv, char **envp);
void	ft_free_strs(char **board, int i);

char	*ft_get_path(char *cmd, char **envp);

#endif