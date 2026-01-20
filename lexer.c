/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/20 19:56:03 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_skip_spaces(const char *s, int i)
{
	while (s[i] && ms_is_space(s[i]))
		i++;
	return (i);
}

static int	ms_add_operator(const char *s, int i, t_token **list)
{
	t_token_type	type;
	t_token			*token;
	int				advance;

	advance = ms_operator_advance(s, i, &type);
	if (!advance)
		return (-1);
	token = ms_token_new(type, NULL);
	if (!token)
		return (-1);
	ms_token_add_back(list, token);
	return (i + advance);
}

static int	ms_add_word(const char *s, int i, t_token **list, t_shell *shell)
{
	t_token	*token;
	char	*value;
	int		next;

	value = NULL;
	next = ms_read_word(s, i, &value, shell);
	if (next < 0)
	{
		free(value);
		return (-1);
	}
	if (!value)
		return (-1);
	token = ms_token_new(TOKEN_WORD, value);
	free(value);
	if (!token)
		return (-1);
	ms_token_add_back(list, token);
	return (next);
}

t_token	*ms_lexer(const char *input, t_shell *shell)
{
	t_token	*list;
	int		index;
	int		next;

	if (!input)
		return (NULL);
	list = NULL;
	index = 0;
	while (input[index])
	{
		index = ms_skip_spaces(input, index);
		if (!input[index])
			break ;
		if (ms_is_operator(input[index]))
			next = ms_add_operator(input, index, &list);
		else
			next = ms_add_word(input, index, &list, shell);
		if (next < 0)
			return (ms_token_clear(&list), NULL);
		index = next;
	}
	return (list);
}
