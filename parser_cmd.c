/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:40:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 13:33:22 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	ms_redir_from_token(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

static int	ms_add_redir(t_parser *parser, t_simple_cmd *cmd)
{
	t_redir			*redir;
	t_redir_type	kind;
	char			*word;
	t_token_type	type;

	type = parser->current->type;
	kind = ms_redir_from_token(type);
	if (!ms_parser_consume(parser, type))
		return (0);
	if (!ms_parser_expect_word(parser, &word))
		return (0);
	redir = ms_redir_new(kind, word);
	if (!redir)
	{
		free(word);
		return (0);
	}
	ms_redir_add_back(&cmd->redir, redir);
	return (1);
}

static int	ms_add_word(t_parser *parser, t_simple_cmd *cmd)
{
	if (!ms_parser_add_arg(cmd, parser->current->value))
		return (0);
	ms_parser_consume(parser, TOKEN_WORD);
	return (1);
}

static int	ms_parse_simple_step(t_parser *parser, t_simple_cmd *cmd)
{
	t_token_type	type;

	type = parser->current->type;
	if (type == TOKEN_WORD)
		return (ms_add_word(parser, cmd));
	return (ms_add_redir(parser, cmd));
}

t_simple_cmd	*ms_parse_simple_cmd(t_parser *parser)
{
	t_simple_cmd	*cmd;
	int				has_content;
	t_token_type	type;

	if (!parser || !parser->current)
		return (NULL);
	cmd = ms_simple_cmd_new();
	if (!cmd)
		return (NULL);
	has_content = 0;
	type = parser->current->type;
	while (parser->current && ms_parser_token_is_word_or_redir(type))
	{
		if (!ms_parse_simple_step(parser, cmd))
			return (ms_simple_cmd_clear(&cmd), NULL);
		has_content = 1;
		if (parser->current)
			type = parser->current->type;
		else
			type = TOKEN_END;
	}
	if (!has_content)
		return (ms_simple_cmd_clear(&cmd), NULL);
	return (cmd);
}
