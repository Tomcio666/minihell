/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:31:32 by tloin             #+#    #+#             */
/*   Updated: 2025/09/30 13:41:07 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*wyn;

	i = -1;
	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	wyn = (char *)malloc(len + 1);
	if (!wyn)
		return (NULL);
	while (++i < len)
		wyn[i] = f((unsigned int)i, s[i]);
	wyn[i] = '\0';
	return (wyn);
}
