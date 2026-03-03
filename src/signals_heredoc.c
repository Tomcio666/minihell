/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:55:27 by mgumienn          #+#    #+#             */
/*   Updated: 2026/03/03 17:04:50 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_sig_handler_heredoc(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
		rl_done = 1;
	ms_signal_set(sig);
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
	ms_signal_set(sig);
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
