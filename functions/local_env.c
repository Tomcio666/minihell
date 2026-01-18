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
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (&env[i + 1]);
}

void	local_env_clear(t_shell *s_shell)
{
	int	i;

	i = -1;
	while (s_shell->env[++i])
		free(s_shell->env[i]);
	free(s_shell->env);
}

char	**get_env(char *name, t_shell *s_shell)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = strlen(name);
	while (s_shell->env[++i])
	{
		j = -1;
		while (s_shell->env[i][++j]
			&& s_shell->env[i][j] != '='
			&& s_shell->env[i][j] == name[j])
			if (j == len - 1 && s_shell->env[i][j + 1] == '=')
				return (&(s_shell->env[i]));
	}
	return (NULL);
}

void	load_env(t_shell *s_shell)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	if (s_shell->env != NULL)
		local_env_clear(s_shell);
	s_shell->env = malloc((i + 1) * sizeof(char *));
	s_shell->env[i] = NULL;
	while (--i >= 0)
		s_shell->env[i] = strdup(environ[i]);
}
