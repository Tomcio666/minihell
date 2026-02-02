/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 18:04:35 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H

# include "ms_types.h"

int		ms_execute_node(t_ast *node, t_exec_ctx *ctx);
int		ms_execute_ast(t_ast *node, t_shell *shell);
int		execute_executable(const char *path, char **argv, t_shell *shell);

int		ms_has_slash(const char *s);
void	ms_free_split(char **arr);
char	**ms_env_path(t_shell *shell);
char	*ms_path_join(const char *dir, const char *cmd);
int		ms_exec_search(t_simple_cmd *cmd, t_shell *shell);

int		ms_dup_io(int in_fd, int out_fd);
int		ms_is_builtin(t_simple_cmd *cmd);
int		ms_execute_builtin_only(t_simple_cmd *cmd, t_shell *shell);
int		ms_execute_builtin(t_simple_cmd *cmd, t_shell *shell);
int		ms_execute_simple_cmd(t_simple_cmd *cmd, t_shell *shell);

int		ms_execute_child(t_ast *node, int in_fd, int out_fd, t_shell *shell);
int		ms_wait_children(pid_t left_pid, pid_t right_pid);
int		ms_execute_pipe(t_ast *node, int in_fd, int out_fd, t_shell *shell);
int		ms_execute_logic(t_ast *node, t_exec_ctx *ctx);
int		node_no_command(t_ast *node);

#endif
