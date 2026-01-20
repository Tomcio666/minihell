/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:40:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/20 16:42:40 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*ms_parse_and_or(t_parser *parser);

static t_token_type	ms_current_type(t_parser *parser)
{
	if (!parser || !parser->current)
		return (TOKEN_END);
	return (parser->current->type);
}

static t_ast	*ms_join_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ms_ast_new(type);
	if (!node)
	{
		ms_ast_clear(&left);
		ms_ast_clear(&right);
		return (NULL);
	}
	ms_ast_attach_children(node, left, right);
	return (node);
}

static t_ast	*ms_wrap_subshell(t_ast *inner)
{
	t_ast	*node;

	node = ms_ast_new(NODE_SUBSHELL);
	if (!node)
	{
		ms_ast_clear(&inner);
		return (NULL);
	}
	ms_ast_attach_children(node, inner, NULL);
	return (node);
}

static t_ast	*ms_parse_subshell(t_parser *parser)
{
	t_ast	*node;

	ms_parser_consume(parser, TOKEN_LPAREN);
	node = ms_parse_and_or(parser);
	if (!node)
		return (NULL);
	if (!ms_parser_consume(parser, TOKEN_RPAREN))
	{
		ms_ast_clear(&node);
		return (NULL);
	}
	return (ms_wrap_subshell(node));
}

static t_ast	*ms_parse_term(t_parser *parser)
{
	t_simple_cmd	*cmd;
	t_ast			*node;

	if (ms_current_type(parser) == TOKEN_LPAREN)
		return (ms_parse_subshell(parser));
	cmd = ms_parse_simple_cmd(parser);
	if (!cmd)
		return (NULL);
	node = ms_ast_new(NODE_SIMPLE_CMD);
	if (!node)
	{
		ms_simple_cmd_clear(&cmd);
		return (NULL);
	}
	ms_ast_set_command(node, cmd);
	return (node);
}

static t_ast	*ms_parse_pipeline(t_parser *parser)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = ms_parse_term(parser);
	if (!left)
		return (NULL);
	while (ms_current_type(parser) == TOKEN_PIPE)
	{
		ms_parser_consume(parser, TOKEN_PIPE);
		right = ms_parse_term(parser);
		if (!right)
		{
			ms_ast_clear(&left);
			return (NULL);
		}
		node = ms_join_node(NODE_PIPE, left, right);
		if (!node)
			return (NULL);
		left = node;
	}
	return (left);
}

static t_ast	*ms_parse_and_or(t_parser *parser)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*node;
	t_node_type		type;
	t_token_type	tok;

	left = ms_parse_pipeline(parser);
	if (!left)
		return (NULL);
	tok = ms_current_type(parser);
	while (tok == TOKEN_AND_IF || tok == TOKEN_OR_IF)
	{
		type = NODE_AND;
		if (tok == TOKEN_OR_IF)
			type = NODE_OR;
		ms_parser_consume(parser, tok);
		right = ms_parse_pipeline(parser);
		if (!right)
			return (ms_ast_clear(&left), NULL);
		node = ms_join_node(type, left, right);
		if (!node)
			return (NULL);
		left = node;
		tok = ms_current_type(parser);
	}
	return (left);
}

t_ast	*ms_parse(t_token *tokens)
{
	t_parser	parser;
	t_ast		*node;

	parser.current = tokens;
	node = ms_parse_and_or(&parser);
	if (!node)
		return (NULL);
	if (parser.current)
	{
		ms_ast_clear(&node);
		return (NULL);
	}
	return (node);
}
