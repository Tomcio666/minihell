/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:20:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 16:59:57 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_execute_node(t_ast *node, t_exec_ctx *ctx);

static int	node_type_zero(t_ast *node, t_exec_ctx *ctx, pid_t pid)
{
	int		status;

	if (!node->command || !node->command->argv || !node->command->argv[0])
		return (node_no_command(node));
	if (ctx->in_child)
		return (ms_execute_simple_cmd(node->command, ctx->shell));
	if (ms_is_builtin(node->command))
		return (ms_execute_builtin(node->command, ctx->shell));
	pid = fork();
	if (pid == 0)
		_exit(ms_execute_child(node, ctx->in_fd, ctx->out_fd, ctx->shell));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static int	ms_execute_node(t_ast *node, t_exec_ctx *ctx)
{
	pid_t	pid;

	pid = 0;
	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
		return (ms_execute_pipe(node, ctx->in_fd, ctx->out_fd, ctx->shell));
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (ms_execute_logic(node, ctx));
	if (node->type == NODE_SUBSHELL)
	{
		if (ctx->in_child)
			return (ms_execute_node(node->left, ctx));
		pid = fork();
		if (pid == 0)
			_exit(ms_execute_child(node->left, ctx->in_fd, ctx->out_fd,
					ctx->shell));
		waitpid(pid, NULL, 0);
		return (0);
	}
	if (node->type == NODE_SIMPLE_CMD)
		return (node_type_zero(node, ctx, pid));
	return (1);
}

int	ms_execute_ast(t_ast *node, t_shell *shell)
{
	t_exec_ctx	ctx;

	ctx.in_fd = STDIN_FILENO;
	ctx.out_fd = STDOUT_FILENO;
	ctx.shell = shell;
	ctx.in_child = 0;
	return (ms_execute_node(node, &ctx));
}
