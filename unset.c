/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:45:06 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/18 18:34:03 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_cmd(char **env, t_shell *shell, t_simple_cmd *cmd)
{
	printf("unset got arg: %s\n", *(env));
	if (env == NULL)
		return (0);
	free(*env);
	*env = strdup("[deleted]");
	printf("unset changed to: %s\n", *(env));
	env_cmd(shell, cmd);
	return (1);
}
