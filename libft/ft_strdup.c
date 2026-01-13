/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:26:27 by tloin             #+#    #+#             */
/*   Updated: 2025/10/03 12:22:37 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*strdup;
	int		i;

	i = 0;
	while (s[i])
		i++;
	strdup = malloc(i + 1);
	if (!strdup)
		return (NULL);
	i = -1;
	while (s[++i])
		strdup[i] = s[i];
	strdup[i] = '\0';
	return (strdup);
}
