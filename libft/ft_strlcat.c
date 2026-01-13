/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:44:34 by tloin             #+#    #+#             */
/*   Updated: 2025/10/03 12:03:50 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dsize;
	size_t	ssize;

	i = 0;
	dsize = 0;
	ssize = 0;
	if (dst != NULL)
		while (dst[dsize] != '\0')
			dsize++;
	if (src != NULL)
		while (src[ssize] != '\0')
			ssize++;
	j = dsize;
	if (size <= dsize)
		return (ssize + size);
	while (src[i] && i < size - dsize - 1)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dsize + ssize);
}
