
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:45:39 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/17 18:35:21 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_env(char *env)
{
	int	i;

	i = 0;
	if(ft_strchr(env, '='))
	{
		while (env[i] && env[i] != '=')
			i++;
		return (&env[i + 1]);
	}
	return (NULL);
}

void	local_env_clear(t_shell *shell)
{
	int	index;

	if (!shell || !shell->env)
		return ;
	index = 0;
	while (shell->env[index])
		free(shell->env[index++]);
	free(shell->env);
	shell->env = NULL;
}

char	**get_env(const char *name, t_shell *shell)
{
	int	index;
	int	len;

	if (!shell || !shell->env || !name)
		return (NULL);
	len = (int)ft_strlen(name);
	index = 0;
	while (shell->env[index])
	{
		if (ft_strncmp(shell->env[index], name, len) == 0
			&& shell->env[index][len] == '=')
			return (&shell->env[index]);
		index++;
	}
	return (NULL);
}

void	load_env(t_shell *shell)
{
	extern char	**environ;
	int			count;

	count = 0;
	while (environ[count])
		count++;
	local_env_clear(shell);
	shell->env = malloc(sizeof(char *) * (count + 1));
	if (!shell->env)
		return ;
	shell->env[count] = NULL;
	while (count-- > 0)
		shell->env[count] = ft_strdup(environ[count]);
}

static char	*ms_env_join(const char *name, const char *value)
{
	char	*tmp;
	char	*pair;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	pair = ft_strjoin(tmp, value);
	free(tmp);
	return (pair);
}

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
