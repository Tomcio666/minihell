/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:36:42 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/02 17:22:15 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_executable(const char *path, char **argv, t_shell *shell)
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
