/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:32:25 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 12:04:01 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

int	g_signal;

void	switch_signal_print(void)
{
	struct termios	termios_new;

	tcgetattr(STDIN_FILENO, &termios_new);
	if (termios_new.c_lflag & ECHOCTL)
		termios_new.c_lflag &= ~ECHOCTL;
	else
		termios_new.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}

void	enable_signal_print(void)
{
	struct termios	termios_new;

	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}

void	disable_signal_print(void)
{
	struct termios	termios_new;

	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}

void	sig_quit(int signal)
{
	ft_printf(2, "Quit: 3\n");
	g_signal = signal;
}

void	sig_interrupt(int signal)
{
	g_signal = signal;
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_interrupt_exec(int signal)
{
	g_signal = signal;
}