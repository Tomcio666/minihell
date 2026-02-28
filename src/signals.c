/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:12:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/28 19:32:40 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal;

static void	ms_sig_handler_heredoc(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
	{
		// write(STDOUT_FILENO, "\n", 1);
		rl_done = 1;
	}
	g_signal = sig;
}

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

void	ms_heredoc_signal_mode(int on)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (on)
		sa.sa_sigaction = ms_sig_handler_heredoc;
	else
		sa.sa_sigaction = ms_sig_handler;
	sigaction(SIGINT, &sa, NULL);
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
