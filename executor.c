/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:20:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/26 18:06:41 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_execute_node(t_ast *node, int in_fd, int out_fd,
			t_shell *shell, int in_child);

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

static int	ms_exec_direct(t_simple_cmd *cmd, t_shell *shell)
{
	return (execute_executable(cmd->argv[0], cmd->argv, shell));
}

static int	ms_exec_search(t_simple_cmd *cmd, t_shell *shell)
{
	char	**paths;
	char	*full;
	int	index;

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
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0
		&& cmd->argv[0][4] == '\0')
		return (exit_cmd(shell, cmd));
	return (0);
}

static int	ms_execute_simple_cmd(t_simple_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ms_is_builtin(cmd))
		return (ms_execute_builtin(cmd, shell));
	if (ms_has_slash(cmd->argv[0]))
		return (ms_exec_direct(cmd, shell));
	return (ms_exec_search(cmd, shell));
}

static int	ms_execute_child(t_ast *node, int in_fd, int out_fd,
			t_shell *shell)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	int		status;

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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	return (1);
}

int	ms_execute_ast(t_ast *node, t_shell *shell)
{
	return (ms_execute_node(node, STDIN_FILENO, STDOUT_FILENO, shell, 0));
}
