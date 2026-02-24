/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:10:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/10 18:07:41 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_has_wildcard(const char *s)
{
	int	index;

	if (!s)
		return (0);
	index = 0;
	while (s[index])
	{
		if (s[index] == '*')
			return (1);
		index++;
	}
	return (0);
}

static int	ms_add_literal(t_simple_cmd *cmd, const char *value)
{
	cmd->argv = ms_argv_add(cmd->argv, value);
	if (!cmd->argv)
		return (0);
	return (1);
}

static int	ms_add_matches(t_simple_cmd *cmd, char **matches, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		cmd->argv = ms_argv_add(cmd->argv, matches[index]);
		if (!cmd->argv)
			return (0);
		index++;
	}
	return (1);
}

int	ms_wildcard_expand(t_simple_cmd *cmd, const char *value)
{
	char	**matches;
	int		count;

	if (!cmd || !value)
		return (0);
	if (!ms_has_wildcard(value) || ms_has_slash(value))
		return (ms_add_literal(cmd, value));
	count = 0;
	matches = ms_matches_collect(value, &count);
	if (!matches)
	{
		if (count == 0)
			return (ms_add_literal(cmd, value));
		return (0);
	}
	ms_matches_sort(matches, count);
	if (!ms_add_matches(cmd, matches, count))
	{
		ms_free_split(matches);
		return (0);
	}
	ms_free_split(matches);
	return (1);
}
