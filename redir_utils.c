/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:14:32 by tloin             #+#    #+#             */
/*   Updated: 2026/01/28 15:25:56 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_is_delim(const char *line, const char *delim)
{
	if (!line || !delim)
		return (0);
	return (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0);
}

static int	ms_heredoc_fd(const char *delim)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ms_is_delim(line, delim))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static int	ms_redir_open(t_redir *redir)
{
	if (redir->kind == REDIR_IN)
		return (open(redir->word, O_RDONLY));
	if (redir->kind == REDIR_OUT)
		return (open(redir->word, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (redir->kind == REDIR_APPEND)
		return (open(redir->word, O_CREAT | O_WRONLY | O_APPEND, 0644));
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
			perror(redir->word);
			return (1);
		}
		if (redir->kind == REDIR_IN || redir->kind == REDIR_HEREDOC)
			ms_set_fd(in_fd, fd);
		else
			ms_set_fd(out_fd, fd);
		redir = redir->next;
	}
	return (0);
}