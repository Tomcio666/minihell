/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:49:01 by mgumienn          #+#    #+#             */
/*   Updated: 2026/03/09 16:52:10 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_heredoc_event_hook(void)
{
	if (ms_signal_get() == SIGINT)
		rl_done = 1;
	return (0);
}

static int	ms_heredoc_event(const char *delim, int *pipefd)
{
	char	*line;

	while (1)
	{
		if (ms_signal_get() == SIGINT)
			break ;
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ms_process_heredoc_line(line, delim, pipefd))
			break ;
	}
	return (ms_signal_get() == SIGINT);
}

static int	ms_heredoc_fd_util(const char *delim, int *pipefd, int save_in)
{
	int		interrupted;

	ms_heredoc_signal_mode(1);
	rl_event_hook = ms_heredoc_event_hook;
	rl_set_keyboard_input_timeout(10000);
	interrupted = ms_heredoc_event(delim, pipefd);
	rl_event_hook = NULL;
	rl_set_keyboard_input_timeout(0);
	ms_heredoc_signal_mode(0);
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	return (interrupted);
}

int	ms_heredoc_fd(const char *delim)
{
	int		pipefd[2];
	int		save_in;

	save_in = ms_setup_heredoc_stdin();
	if (pipe(pipefd) < 0)
		return (ms_restore_stdin_on_error(save_in));
	if (ms_heredoc_fd_util(delim, pipefd, save_in))
		return (ms_cleanup_heredoc_error(pipefd));
	close(pipefd[1]);
	return (pipefd[0]);
}
