/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:49:01 by mgumienn          #+#    #+#             */
/*   Updated: 2026/03/03 16:50:59 by mgumienn         ###   ########.fr       */
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
		line = readline("heredoc> ");
		if (!line || !delim || ms_signal_get() == SIGINT)
		{
			free(line);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	return ((ms_signal_get() == SIGINT));
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
	int		tty;

	save_in = dup(STDIN_FILENO);
	tty = open("/dev/tty", O_RDONLY);
	if (tty >= 0)
	{
		dup2(tty, STDIN_FILENO);
		close(tty);
	}
	if (pipe(pipefd) < 0)
	{
		if (save_in >= 0)
		{
			dup2(save_in, STDIN_FILENO);
			close(save_in);
		}
		return (-1);
	}
	if (ms_heredoc_fd_util(delim, pipefd, save_in))
		return (close(pipefd[0]), close(pipefd[1]), -1);
	close(pipefd[1]);
	return (pipefd[0]);
}
