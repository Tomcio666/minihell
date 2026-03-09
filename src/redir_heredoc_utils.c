/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:51:01 by tloin             #+#    #+#             */
/*   Updated: 2026/03/09 17:00:30 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_setup_heredoc_stdin(void)
{
	int		save_in;
	int		tty;

	save_in = dup(STDIN_FILENO);
	tty = open("/dev/tty", O_RDONLY);
	if (tty >= 0)
	{
		dup2(tty, STDIN_FILENO);
		close(tty);
	}
	return (save_in);
}

int	ms_restore_stdin_on_error(int save_in)
{
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	return (-1);
}

int	ms_cleanup_heredoc_error(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}

int	ms_process_heredoc_line(char *line, const char *delim, int *pipefd)
{
	if (ms_signal_get() == SIGINT)
	{
		free(line);
		return (1);
	}
	if (!delim)
	{
		free(line);
		return (1);
	}
	if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
	{
		free(line);
		return (1);
	}
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
	return (0);
}
