/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:51:50 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/02 16:58:39 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_dup_io(int in_fd, int out_fd)
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

int	ms_is_builtin(t_simple_cmd *cmd)
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

int	ms_execute_builtin_only(t_simple_cmd *cmd, t_shell *shell)
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

int	ms_execute_builtin(t_simple_cmd *cmd, t_shell *shell)
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

int	ms_execute_simple_cmd(t_simple_cmd *cmd, t_shell *shell)
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
