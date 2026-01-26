/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:36:42 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/26 17:05:44 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_executable(const char *path, char **argv, t_shell *shell)
{
	execve(path, argv, shell->env);
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (127);
	}
	perror(path);
	return (126);
}
