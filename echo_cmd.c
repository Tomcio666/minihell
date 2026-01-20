/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:08:09 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/18 17:48:41 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_echo_is_nflag(const char *s)
{
	int	index;

	if (!s || s[0] != '-')
		return (0);
	index = 1;
	if (!s[index])
		return (0);
	while (s[index] == 'n')
		index++;
	return (s[index] == '\0');
}

int	echo_cmd(t_simple_cmd *cmd)
{
	int	index;
	int	newline;

	if (!cmd || !cmd->argv)
		return (1);
	index = 1;
	newline = 1;
	while (cmd->argv[index] && ms_echo_is_nflag(cmd->argv[index]))
	{
		newline = 0;
		index++;
	}
	while (cmd->argv[index])
	{
		printf("%s", cmd->argv[index]);
		if (cmd->argv[index + 1])
			printf(" ");
		index++;
	}
	if (newline)
		printf("\n");
	return (0);
}