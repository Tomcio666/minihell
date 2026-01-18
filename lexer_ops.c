/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 11:04:55 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_set_type(t_token_type *type, t_token_type value)
{
	*type = value;
	return (1);
}

static int	ms_operator_double(const char *s, int i, t_token_type *type)
{
	if (s[i] == '&' && s[i + 1] == '&')
	{
		*type = TOKEN_AND_IF;
		return (2);
	}
	if (s[i] == '|' && s[i + 1] == '|')
	{
		*type = TOKEN_OR_IF;
		return (2);
	}
	if (s[i] == '<' && s[i + 1] == '<')
	{
		*type = TOKEN_HEREDOC;
		return (2);
	}
	if (s[i] == '>' && s[i + 1] == '>')
	{
		*type = TOKEN_REDIR_APPEND;
		return (2);
	}
	return (0);
}

int	ms_operator_advance(const char *s, int i, t_token_type *type)
{
	int	advance;

	advance = ms_operator_double(s, i, type);
	if (advance)
		return (advance);
	if (s[i] == '|')
		return (ms_set_type(type, TOKEN_PIPE));
	if (s[i] == '<')
		return (ms_set_type(type, TOKEN_REDIR_IN));
	if (s[i] == '>')
		return (ms_set_type(type, TOKEN_REDIR_OUT));
	if (s[i] == '(')
		return (ms_set_type(type, TOKEN_LPAREN));
	if (s[i] == ')')
		return (ms_set_type(type, TOKEN_RPAREN));
	return (0);
}
