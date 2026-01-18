/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:38:54 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/17 19:46:19 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_shell *s_shell)
{
	int	i;
	int	j;

	i = -1;
	while (s_shell->env[++i])
	{
		if (strchr(s_shell->env[i], '='))
		{
			j = -1;
			printf("declare -x ");
			while (s_shell->env[i][++j] != '=')
				printf("%c", s_shell->env[i][j]);
			printf("=\"");
			printf("%s", trim_env(s_shell->env[i]));
			printf("\"\n");
		}
	}
}
