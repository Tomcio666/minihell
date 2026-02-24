/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:12:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/08 13:33:48 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal;

static void	ms_sig_handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (rl_readline_state & RL_STATE_READCMD && sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
	}
	g_signal = sig;
}

void	ms_signals_setup(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ms_sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
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
