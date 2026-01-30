/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:20:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/30 16:45:44 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_execute_node(t_ast *node, t_exec_ctx *ctx);

static int	ms_has_slash(const char *s)
{
	int	index;

	index = 0;
	while (s && s[index])
	{
		if (s[index] == '/')
			return (1);
		index++;
	}
	return (0);
}

static void	ms_free_split(char **arr)
{
	int	index;

	if (!arr)
		return ;
	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

static char	**ms_env_path(t_shell *shell)
{
	char	**slot;
	char	*value;

	slot = get_env("PATH", shell);
	if (!slot)
		return (NULL);
	value = trim_env(*slot);
	if (!value)
		return (NULL);
	return (ft_split(value, ':'));
}

static char	*ms_path_join(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static int	ms_exec_search(t_simple_cmd *cmd, t_shell *shell)
{
	char	**paths;
	char	*full;
	int		index;

	paths = ms_env_path(shell);
	if (!paths)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (127);
	}
	index = 0;
	while (paths[index])
	{
		full = ms_path_join(paths[index], cmd->argv[0]);
		if (!full)
			return (ms_free_split(paths), 1);
		if (access(full, X_OK) == 0)
			return (execute_executable(full, cmd->argv, shell));
		free(full);
		index++;
	}
	ms_free_split(paths);
	ft_putstr_fd("minishell: command not found\n", 2);
	return (127);
}

static int	ms_dup_io(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) < 0)
			return (1);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) < 0)
			return (1);
		close(out_fd);
	}
	return (0);
}

static int	ms_is_builtin(t_simple_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0 && cmd->argv[0][3] == '\0')
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0 && cmd->argv[0][4] == '\0')
		return (1);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0 && cmd->argv[0][2] == '\0')
		return (1);
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0 && cmd->argv[0][3] == '\0')
		return (1);
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0
		&& cmd->argv[0][6] == '\0')
		return (1);
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0
		&& cmd->argv[0][5] == '\0')
		return (1);
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0
		&& cmd->argv[0][4] == '\0')
		return (1);
	return (0);
}

static int	ms_execute_builtin_only(t_simple_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0 && cmd->argv[0][3] == '\0')
		return (pwd_command());
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0 && cmd->argv[0][4] == '\0')
		return (echo_cmd(cmd));
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0 && cmd->argv[0][2] == '\0')
		return (cd_cmd(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0 && cmd->argv[0][3] == '\0')
		return (env_cmd(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0
		&& cmd->argv[0][6] == '\0')
		return (export_cmd(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0
		&& cmd->argv[0][5] == '\0')
		return (unset_cmd(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0
		&& cmd->argv[0][4] == '\0')
		return (exit_cmd(shell, cmd));
	return (0);
}

static int	ms_execute_builtin(t_simple_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = -1;
	saved_out = -1;
	if (ms_redir_apply(cmd, &saved_in, &saved_out) != 0)
	{
		ms_redir_restore(saved_in, saved_out);
		return (1);
	}
	status = ms_execute_builtin_only(cmd, shell);
	ms_redir_restore(saved_in, saved_out);
	return (status);
}

static int	ms_execute_simple_cmd(t_simple_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ms_redir_apply(cmd, NULL, NULL) != 0)
		return (1);
	if (ms_is_builtin(cmd))
		return (ms_execute_builtin_only(cmd, shell));
	if (ms_has_slash(cmd->argv[0]))
		return (execute_executable(cmd->argv[0], cmd->argv, shell));
	return (ms_exec_search(cmd, shell));
}

static int	ms_execute_child(t_ast *node, int in_fd, int out_fd, t_shell *shell)
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
	return (status);
}

static int	ms_wait_children(pid_t left_pid, pid_t right_pid)
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

static int	ms_execute_pipe(t_ast *node, int in_fd, int out_fd,
			t_shell *shell)
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

static int	ms_execute_logic(t_ast *node, t_exec_ctx *ctx)
{
	int	status;

	status = ms_execute_node(node->left, ctx);
	if (node->type == NODE_AND && status == 0)
		return (ms_execute_node(node->right, ctx));
	if (node->type == NODE_OR && status != 0)
		return (ms_execute_node(node->right, ctx));
	return (status);
}

static int	node_no_command(t_ast *node)
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
