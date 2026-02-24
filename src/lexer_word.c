/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 16:30:46 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_append_char(char *s, char c)
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

char	*ms_append_str(char *s, const char *add)
{
	char	*new_str;
	size_t	len;
	size_t	add_len;

	if (!add)
		return (s);
	len = 0;
	if (s)
		len = ft_strlen(s);
	add_len = ft_strlen(add);
	new_str = malloc(sizeof(char) * (len + add_len + 1));
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	if (s)
		ft_memcpy(new_str, s, len);
	ft_memcpy(new_str + len, add, add_len);
	new_str[len + add_len] = '\0';
	free(s);
	return (new_str);
}

int	ms_expand_status(t_lex_state *st)
{
	char	*status;
	int		value;

	value = 0;
	if (st->shell)
		value = st->shell->last_status;
	status = ft_itoa(value);
	if (!status)
		return (-1);
	*st->out = ms_append_str(*st->out, status);
	free(status);
	if (!*st->out)
		return (-1);
	return (0);
}

int	ms_append_dollar(t_lex_state *st)
{
	*st->out = ms_append_char(*st->out, '$');
	if (!*st->out)
		return (-1);
	return (0);
}

int	ms_expand_var_cases(t_lex_state *st, int i)
{
	if (!st->s[i])
	{
		if (ms_append_dollar(st) != 0)
			return (-1);
		return (i);
	}
	if (st->s[i] == '?')
	{
		if (ms_expand_status(st) != 0)
			return (-1);
		return (i + 1);
	}
	if (!(ft_isalpha(st->s[i]) || st->s[i] == '_'))
	{
		if (ms_append_dollar(st) != 0)
			return (-1);
		return (i);
	}
	return (-10);
}
