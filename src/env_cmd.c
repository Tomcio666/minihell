/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:08:06 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/20 17:35:40 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	env_cmd(t_shell *shell, t_simple_cmd *cmd)
{
	int	index;

	(void)cmd;
	if (!shell || !shell->env)
		return (1);
	if (cmd && cmd->argv && cmd->argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	index = 0;
	while (shell->env[index])
	{
		if (ft_strchr(shell->env[index], '='))
			printf("%s\n", shell->env[index]);
		index++;
	}
	return (0);
}
