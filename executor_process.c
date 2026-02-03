/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:00:29 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/03 18:19:07 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute_child(t_ast *node, int in_fd, int out_fd, t_shell *shell)
{
	int				status;
	t_exec_ctx		ctx;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ms_dup_io(in_fd, out_fd) != 0)
		return (1);
	ctx.in_fd = STDIN_FILENO;
	ctx.out_fd = STDOUT_FILENO;
	ctx.shell = shell;
	ctx.in_child = 1;
	status = ms_execute_node(node, &ctx);
	ms_ast_clear(&node);
	local_env_clear(shell);
	return (status);
}

int	ms_wait_children(pid_t left_pid, pid_t right_pid)
{
	int	status;

	status = 0;
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	ms_execute_pipe(t_ast *node, int in_fd, int out_fd, t_shell *shell)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipefd) < 0)
		return (1);
	left_pid = fork();
	if (left_pid == 0)
	{
		close(pipefd[0]);
		_exit(ms_execute_child(node->left, in_fd, pipefd[1], shell));
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		close(pipefd[1]);
		_exit(ms_execute_child(node->right, pipefd[0], out_fd, shell));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (ms_wait_children(left_pid, right_pid));
}

int	ms_execute_logic(t_ast *node, t_exec_ctx *ctx)
{
	int	status;

	status = ms_execute_node(node->left, ctx);
	if (node->type == NODE_AND && status == 0)
		return (ms_execute_node(node->right, ctx));
	if (node->type == NODE_OR && status != 0)
		return (ms_execute_node(node->right, ctx));
	return (status);
}

int	node_no_command(t_ast *node)
{
	int	saved_in;
	int	saved_out;

	saved_in = -1;
	saved_out = -1;
	if (ms_redir_apply(node->command, &saved_in, &saved_out) != 0)
	{
		ms_redir_restore(saved_in, saved_out);
		return (1);
	}
	ms_redir_restore(saved_in, saved_out);
	return (0);
}
