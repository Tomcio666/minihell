/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/30 16:29:44 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*ms_append_str(char *s, const char *add)
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

static int	ms_expand_status(t_lex_state *st)
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

static int	ms_append_dollar(t_lex_state *st)
{
	*st->out = ms_append_char(*st->out, '$');
	if (!*st->out)
		return (-1);
	return (0);
}

static int	ms_expand_var_cases(t_lex_state *st, int i)
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

static int	ms_expand_var(t_lex_state *st, int i)
{
	int		start;
	int		cases_return;
	char	*name;
	char	**slot;

	cases_return = ms_expand_var_cases(st, i);
	if (cases_return != -10)
		return (cases_return);
	start = i;
	while (st->s[i] && (ft_isalnum(st->s[i]) || st->s[i] == '_'))
		i++;
	name = ft_substr(st->s, start, i - start);
	if (!name)
		return (-1);
	slot = get_env(name, st->shell);
	if (slot)
		*st->out = ms_append_str(*st->out, trim_env(*slot));
	free(name);
	if (!*st->out)
		return (-1);
	return (i);
}

static int	ms_read_quote(t_lex_state *st, int i, char quote)
{
	while (st->s[i] && st->s[i] != quote)
	{
		if (quote == '"' && st->s[i] == '$')
		{
			i = ms_expand_var(st, i + 1);
			if (i < 0)
				return (-1);
		}
		else
		{
			*st->out = ms_append_char(*st->out, st->s[i]);
			if (!*st->out)
				return (-1);
			i++;
		}
	}
	if (!st->s[i])
		return (-1);
	return (i + 1);
}

int	ms_read_word(t_lex_state st, int i)
{
	while (st.s[i] && !ms_is_space(st.s[i]) && !ms_is_operator(st.s[i]))
	{
		if (st.s[i] == '\'' || st.s[i] == '"')
		{
			i = ms_read_quote(&st, i + 1, st.s[i]);
			if (i < 0)
				return (-1);
		}
		else if (st.s[i] == '$')
		{
			i = ms_expand_var(&st, i + 1);
			if (i < 0)
				return (-1);
		}
		else
		{
			*st.out = ms_append_char(*st.out, st.s[i]);
			if (!*st.out)
				return (-1);
			i++;
		}
	}
	return (i);
}
