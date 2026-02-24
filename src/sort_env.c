/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:04:19 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/10 16:31:24 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp_envs(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == '=' && s2[i] != '=')
			return (-1);
		if (s2[i] == '=' && s1[i] != '=')
			return (1);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	count_envs(t_shell *shell)
{
	int	count;

	count = 0;
	while (shell->env[count])
		count++;
	return (count);
}

t_shell	sort_env(t_shell sorted)
{
	int		i;
	int		j;
	int		count;
	char	*tmp_str;

	count = count_envs(&sorted);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp_envs(sorted.env[j], sorted.env[j + 1]) > 0)
			{
				tmp_str = sorted.env[j];
				sorted.env[j] = sorted.env[j + 1];
				sorted.env[j + 1] = tmp_str;
			}
			j++;
		}
		i++;
	}
	return (sorted);
}
