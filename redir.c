/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:05:10 by tloin             #+#    #+#             */
/*   Updated: 2026/01/28 15:26:10 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_redir_apply(t_simple_cmd *cmd, int *saved_in, int *saved_out)
{
	int	in_fd;
	int	out_fd;

	if (saved_in)
		*saved_in = dup(STDIN_FILENO);
	if (saved_out)
		*saved_out = dup(STDOUT_FILENO);
	if (saved_in && *saved_in < 0)
		return (1);
	if (saved_out && *saved_out < 0)
		return (1);
	if (ms_redir_collect(cmd, &in_fd, &out_fd) != 0)
		return (1);
	if (in_fd >= 0 && dup2(in_fd, STDIN_FILENO) < 0)
		return (close(in_fd), 1);
	if (out_fd >= 0 && dup2(out_fd, STDOUT_FILENO) < 0)
		return (close(out_fd), 1);
	if (in_fd >= 0)
		close(in_fd);
	if (out_fd >= 0)
		close(out_fd);
	return (0);
}

void	ms_redir_restore(int saved_in, int saved_out)
{
	if (saved_in >= 0)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out >= 0)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}
