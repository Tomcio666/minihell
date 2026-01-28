/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:32:41 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/28 16:32:57 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_env_count(t_shell *shell)
{
	int	count;

	count = 0;
	while (shell && shell->env && shell->env[count])
		count++;
	return (count);
}

static int	ms_env_replace(char **slot, char *pair)
{
	if (!slot || !pair)
		return (0);
	free(*slot);
	*slot = pair;
	return (1);
}

static int	ms_env_append(t_shell *shell, char *pair)
{
	char	**new_env;
	int		count;
	int		index;

	count = ms_env_count(shell);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(pair);
		return (0);
	}
	index = 0;
	while (shell->env && shell->env[index])
	{
		new_env[index] = shell->env[index];
		index++;
	}
	new_env[index++] = pair;
	new_env[index] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}

int	ms_env_set(t_shell *shell, const char *name, const char *value)
{
	char	**slot;
	char	*pair;

	if (!shell || !name || !value)
		return (0);
	pair = ms_env_join(name, value);
	if (!pair)
		return (0);
	slot = get_env(name, shell);
	if (slot)
		return (ms_env_replace(slot, pair));
	return (ms_env_append(shell, pair));
}

int	ms_env_unset(t_shell *shell, const char *name)
{
	char	**slot;
	int		index;

	slot = get_env(name, shell);
	if (!slot)
		return (1);
	free(*slot);
	index = (int)(slot - shell->env);
	while (shell->env[index + 1])
	{
		shell->env[index] = shell->env[index + 1];
		index++;
	}
	shell->env[index] = NULL;
	return (1);
}
