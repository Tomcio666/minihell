/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:35:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/12 17:39:28 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmp(const char *left, const char *right)
{
	size_t	len_left;
	size_t	len_right;

	len_left = ft_strlen(left);
	len_right = ft_strlen(right);
	return (ft_strncmp(left, right, len_left + len_right + 1));
}

void	ms_matches_sort(char **list, int count)
{
	int		index;
	int		jndex;
	char	*tmp;

	index = 0;
	while (index < count)
	{
		jndex = 0;
		while (jndex < count - 1 - index)
		{
			if (ms_cmp(list[jndex], list[jndex + 1]) > 0)
			{
				tmp = list[jndex];
				list[jndex] = list[jndex + 1];
				list[jndex + 1] = tmp;
			}
			jndex++;
		}
		index++;
	}
}
