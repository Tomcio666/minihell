/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:45:14 by tloin             #+#    #+#             */
/*   Updated: 2026/01/28 16:04:51 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_token	*ms_token_current(t_parser *parser)
{
	if (!parser)
		return (NULL);
	return (parser->current);
}

static t_token_type	ms_token_type(t_parser *parser)
{
	t_token	*token;

	token = ms_token_current(parser);
	if (!token)
		return (TOKEN_END);
	return (token->type);
}

static void	ms_token_advance(t_parser *parser)
{
	if (parser && parser->current)
		parser->current = parser->current->next;
}

int	ms_parser_expect_word(t_parser *parser, char **out)
{
	t_token	*token;

	if (!parser || !out)
		return (0);
	token = ms_token_current(parser);
	if (!token || token->type != TOKEN_WORD)
		return (0);
	*out = ft_strdup(token->value);
	if (!*out)
		return (0);
	ms_token_advance(parser);
	return (1);
}

int	ms_parser_consume(t_parser *parser, t_token_type type)
{
	if (ms_token_type(parser) != type)
		return (0);
	ms_token_advance(parser);
	return (1);
}
