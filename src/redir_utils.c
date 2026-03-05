/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:14:32 by tloin             #+#    #+#             */
/*   Updated: 2026/03/05 17:47:11 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_redir_open(t_redir *redir)
{
	if (redir->kind == REDIR_IN)
		return (open(redir->word, O_RDONLY));
	if (redir->kind == REDIR_OUT)
		return (open(redir->word, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (redir->kind == REDIR_APPEND)
		return (open(redir->word, O_CREAT | O_WRONLY | O_APPEND, 0644));
	if (redir->kind == REDIR_HEREDOC_FD)
		return (ft_atoi(redir->word));
	return (ms_heredoc_fd(redir->word));
}

static void	ms_set_fd(int *dst, int fd)
{
	if (*dst >= 0)
		close(*dst);
	*dst = fd;
}

int	ms_redir_collect(t_simple_cmd *cmd, int *in_fd, int *out_fd)
{
	int		fd;
	t_redir	*redir;

	redir = NULL;
	if (cmd)
		redir = cmd->redir;
	*in_fd = -1;
	*out_fd = -1;
	while (redir)
	{
		fd = ms_redir_open(redir);
		if (fd < 0)
		{
			if (ms_signal_get() != SIGINT)
				perror(redir->word);
			return (1);
		}
		if (redir->kind == REDIR_IN || redir->kind == REDIR_HEREDOC
			|| redir->kind == REDIR_HEREDOC_FD)
			ms_set_fd(in_fd, fd);
		else
			ms_set_fd(out_fd, fd);
		redir = redir->next;
	}
	return (0);
}
