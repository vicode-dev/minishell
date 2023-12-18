/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:45:12 by jgoudema          #+#    #+#             */
/*   Updated: 2023/12/18 21:15:01 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_temp.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	// (void)(argc + (int)argv);
	get_env(env, &data);
	//ft_cd(&data, argv[argc - 1]);
	ft_pwd(&data);
	// ft_env(&data);
}