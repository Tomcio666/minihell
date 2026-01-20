
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:45:06 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/17 18:40:46 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_cmd(t_shell *shell, t_simple_cmd *cmd)
{
	int	index;
	int	status;

	if (!shell || !cmd || !cmd->argv)
		return (1);
	index = 1;
	status = 0;
	while (cmd->argv[index])
	{
		if (!ms_env_unset(shell, cmd->argv[index]))
			status = 1;
		index++;
	}
	return (status);
}
