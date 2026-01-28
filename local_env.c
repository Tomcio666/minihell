/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:45:39 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/28 16:34:31 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_env(char *env)
{
	int	i;

	i = 0;
	if (ft_strchr(env, '='))
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

char	*ms_env_join(const char *name, const char *value)
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
