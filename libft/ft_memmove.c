/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:55:22 by tloin             #+#    #+#             */
/*   Updated: 2025/09/30 13:50:24 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc = (const char *)src;

	cdest = (char *)dest;
	if (dest <= src)
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	else
	{
		cdest += n - 1;
		csrc += n - 1;
		while (n--)
		{
			*cdest-- = *csrc--;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char str1[] = "maslo";
// 	char str2[] = "dupa";
//
// 	ft_memmove(str1, str2, sizeof(str2));
// 	return (0);
// }