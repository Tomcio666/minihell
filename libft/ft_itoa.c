/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:49:27 by tloin             #+#    #+#             */
/*   Updated: 2025/09/30 13:51:00 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(int n)
{
	int		len;
	long	num;

	num = n;
	len = 0;
	if (n <= 0)
		len = 1;
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static void	ft_itoa_fill(char *str, long num, int len)
{
	if (num == 0)
		str[0] = '0';
	while (num)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	long	num;
	char	*str;

	num = n;
	len = ft_itoa_len(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -num;
	}
	ft_itoa_fill(str, num, len);
	return (str);
}
