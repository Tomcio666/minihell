/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:36:42 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/23 18:53:15 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_executable(t_simple_cmd *cmd, t_shell *shell)
{
	if (execve(cmd->argv[0], &cmd->argv[1], shell->env))
		return (0);
	perror("");
	return (1);
}
