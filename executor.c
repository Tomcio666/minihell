/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:20:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/20 16:43:28 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_execute_node(t_ast *node, int in_fd, int out_fd,
			t_shell *shell, int in_child);

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
	return (0);
}

static int	ms_execute_builtin(t_simple_cmd *cmd, t_shell *shell)
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
	return (0);
}

static int	ms_execute_simple_cmd(t_simple_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ms_is_builtin(cmd))
		return (ms_execute_builtin(cmd, shell));
	printf("command: %s\n", cmd->argv[0]);
	return (0);
}

static int	ms_execute_child(t_ast *node, int in_fd, int out_fd,
			t_shell *shell)
{
	int	status;

	if (ms_dup_io(in_fd, out_fd) != 0)
		return (1);
	status = ms_execute_node(node, STDIN_FILENO, STDOUT_FILENO, shell, 1);
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
		_exit(ms_execute_child(node->left, in_fd, pipefd[1], shell));
	right_pid = fork();
	if (right_pid == 0)
		_exit(ms_execute_child(node->right, pipefd[0], out_fd, shell));
	close(pipefd[0]);
	close(pipefd[1]);
	return (ms_wait_children(left_pid, right_pid));
}

static int	ms_execute_logic(t_ast *node, int in_fd, int out_fd,
			t_shell *shell, int in_child)
{
	int	status;

	status = ms_execute_node(node->left, in_fd, out_fd, shell, in_child);
	if (node->type == NODE_AND && status == 0)
		return (ms_execute_node(node->right, in_fd, out_fd, shell, in_child));
	if (node->type == NODE_OR && status != 0)
		return (ms_execute_node(node->right, in_fd, out_fd, shell, in_child));
	return (status);
}

static int	ms_execute_node(t_ast *node, int in_fd, int out_fd,
			t_shell *shell, int in_child)
{
	pid_t	pid;

	if (!node)
		return (1);
	if (node->type == NODE_PIPE)
		return (ms_execute_pipe(node, in_fd, out_fd, shell));
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (ms_execute_logic(node, in_fd, out_fd, shell, in_child));
	if (node->type == NODE_SUBSHELL)
	{
		if (in_child)
			return (ms_execute_node(node->left, in_fd, out_fd, shell, 1));
		pid = fork();
		if (pid == 0)
			_exit(ms_execute_child(node->left, in_fd, out_fd, shell));
		waitpid(pid, NULL, 0);
		return (0);
	}
	if (node->type == NODE_SIMPLE_CMD)
	{
		if (in_child)
			return (ms_execute_simple_cmd(node->command, shell));
		if (ms_is_builtin(node->command))
			return (ms_execute_builtin(node->command, shell));
		pid = fork();
		if (pid == 0)
			_exit(ms_execute_child(node, in_fd, out_fd, shell));
		waitpid(pid, NULL, 0);
		return (0);
	}
	return (1);
}

int	ms_execute_ast(t_ast *node, t_shell *shell)
{
	return (ms_execute_node(node, STDIN_FILENO, STDOUT_FILENO, shell, 0));
}
