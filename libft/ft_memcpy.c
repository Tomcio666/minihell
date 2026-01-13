/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:47:19 by tloin             #+#    #+#             */
/*   Updated: 2025/09/29 12:54:44 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;
	size_t		i;

	i = -1;
	cdest = (char *)dest;
	csrc = (const char *)src;
	while (++i < n)
		cdest[i] = csrc[i];
	return (dest);
}

// int	main()
// {
// 	char dest[] = "2323";
// 	const char *src = "dupa";
// 	ft_memcpy(dest, src, 2);
// }
