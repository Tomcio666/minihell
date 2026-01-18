/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:08:06 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/15 18:08:50 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmd(t_shell *s_shell)
{
	int			i;

	i = -1;
	while (s_shell->env[++i])
		printf("%s\n", s_shell->env[i]);
	return (0);
}
