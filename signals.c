/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:12:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/05 17:08:34 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal;

static void	ms_sigint_handler(int sig)
{
	(void)sig;
	if (rl_readline_state & RL_STATE_READCMD)
	{
		g_signal = SIGINT;
		rl_on_new_line();
		rl_replace_line("^C", 0);
		rl_redisplay();
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
	}
}

static void	ms_sigquit_handler(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
	if (rl_readline_state & RL_STATE_READCMD)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ms_signals_setup(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ms_sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = ms_sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}

int	ms_signal_get(void)
{
	return (g_signal);
}

void	ms_signal_clear(void)
{
	g_signal = 0;
}
