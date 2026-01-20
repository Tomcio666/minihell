/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 14:24:12 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*ms_append_char(char *s, char c)
{
	char	*new_str;
	size_t	len;

	len = 0;
	if (s)
		len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	if (s)
		ft_memcpy(new_str, s, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}

static int	ms_read_quote(const char *s, int i, char quote, char **out)
{
	while (s[i] && s[i] != quote)
	{
		*out = ms_append_char(*out, s[i]);
		if (!*out)
			return (-1);
		i++;
	}
	if (!s[i])
		return (-1);
	return (i + 1);
}

int	ms_read_word(const char *s, int i, char **out)
{
	char	quote;

	while (s[i] && !ms_is_space(s[i]) && !ms_is_operator(s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			i = ms_read_quote(s, i + 1, quote, out);
			if (i < 0)
				return (-1);
		}
		else
		{
			*out = ms_append_char(*out, s[i]);
			if (!*out)
				return (-1);
			i++;
		}
	}
	return (i);
}
