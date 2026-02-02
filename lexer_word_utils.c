/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:28:10 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/02 16:36:29 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
