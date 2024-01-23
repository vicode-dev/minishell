/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitcode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:39:38 by jgoudema          #+#    #+#             */
/*   Updated: 2024/01/23 15:22:55 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXITCODE_H
# define EXITCODE_H

# define CANNOT_EXEC 126
# define COM_NOT_FOUND 127
# define ERROR_SIG 128
# define INTERRUPT_SIG 130
# define QUIT_SIG 131
# define SYNTAX_ERROR 258

// SIG CODES
# define SIGHUP  1   /* Hangup the process */ 
# define SIGINT  2   /* Interrupt the process */ 
# define SIGQUIT 3   /* Quit the process */ 
# define SIGILL  4   /* Illegal instruction. */ 
# define SIGTRAP 5   /* Trace trap. */ 

#endif