/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:20:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/12 17:11:35 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_match_pattern(const char *pattern, const char *name)
{
	if (!*pattern)
		return (!*name);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*name)
		{
			if (ms_match_pattern(pattern, name))
				return (1);
			name++;
		}
		return (ms_match_pattern(pattern, name));
	}
	if (*pattern == *name)
	{
		return (ms_match_pattern(pattern + 1, name + 1));
	}
	return (0);
}

static int	ms_entry_match(const char *pattern, const char *name)
{
	if (!pattern || !name)
		return (0);
	if (name[0] == '.' && pattern[0] != '.')
		return (0);
	if (ft_strncmp(name, ".", 2) == 0)
		return (0);
	if (ft_strncmp(name, "..", 3) == 0)
		return (0);
	return (ms_match_pattern(pattern, name));
}

static int	ms_collect_add(char ***list, int *count, const char *name)
{
	char	**new_list;

	new_list = ms_argv_add(*list, name);
	if (!new_list)
		return (0);
	*list = new_list;
	(*count)++;
	return (1);
}

static char	**ms_collect_fail(DIR *dir, char **list)
{
	ms_free_split(list);
	closedir(dir);
	return (NULL);
}

char	**ms_matches_collect(const char *pattern, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**list;

	if (!pattern || !count)
		return (NULL);
	*count = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	list = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (ms_entry_match(pattern, entry->d_name))
		{
			if (!ms_collect_add(&list, count, entry->d_name))
				return (ms_collect_fail(dir, list));
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (*count == 0)
		return (NULL);
	return (list);
}
