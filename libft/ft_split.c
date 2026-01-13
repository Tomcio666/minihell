/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:27:17 by tloin             #+#    #+#             */
/*   Updated: 2025/09/29 11:47:53 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	word_count(char *s, char c)
{
	int	count;
	int	inword;

	count = 0;
	inword = 0;
	while (*s)
	{
		if (*s != c && inword == 0)
		{
			inword = 1;
			count++;
		}
		else if (*s == c)
			inword = 0;
		s++;
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	*free_all(char **output, int j)
{
	while (j > 0)
		free(output[--j]);
	free(output);
	return (NULL);
}

static int	fill_split(const char *s, char c, char **result)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			result[j] = word_dup(s, start, i);
			if (!result[j])
				return (free_all(result, j), -1);
			j++;
		}
	}
	result[j] = NULL;
	return (0);
}

char	**ft_split(char *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!result)
		return (NULL);
	if (fill_split(s, c, result))
		return (NULL);
	return (result);
}

// #include <stdio.h>
// int main ()
// {
// 	char **tab;
// 	int i = 0;
// 	tab = ft_split("hello 42 school", ' ');
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }