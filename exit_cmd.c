/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:12:10 by tloin             #+#    #+#             */
/*   Updated: 2026/01/26 18:06:40 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cmd(t_shell *shell, t_simple_cmd *cmd)
{
	int	status;

	if (cmd && cmd->argv && cmd->argv[1])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	status = 0;
	if (shell)
		status = shell->last_status;
	if (shell)
		local_env_clear(shell);
	rl_clear_history();
	exit(status);
	return (0);
}