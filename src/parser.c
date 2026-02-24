/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:40:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 18:19:18 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*ms_parse_and_or(t_parser *parser);

static t_ast	*ms_parse_subshell(t_parser *parser)
{
	t_ast	*inner;
	t_ast	*node;

	ms_parser_consume(parser, TOKEN_LPAREN);
	inner = ms_parse_and_or(parser);
	if (!inner)
		return (NULL);
	if (!ms_parser_consume(parser, TOKEN_RPAREN))
	{
		ms_ast_clear(&inner);
		return (NULL);
	}
	node = ms_ast_new(NODE_SUBSHELL);
	if (!node)
	{
		ms_ast_clear(&inner);
		return (NULL);
	}
	ms_ast_attach_chld(node, inner, NULL);
	return (node);
}

static t_ast	*ms_parse_term(t_parser *parser)
{
	t_simple_cmd	*cmd;
	t_ast			*node;

	if (parser && parser->current
		&& parser->current->type == TOKEN_LPAREN)
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
	while (parser->current && parser->current->type == TOKEN_PIPE)
	{
		ms_parser_consume(parser, TOKEN_PIPE);
		right = ms_parse_term(parser);
		if (!right)
			return (ms_ast_clear(&left), NULL);
		node = ms_ast_new(NODE_PIPE);
		if (!node)
			return (ms_ast_clear(&left), ms_ast_clear(&right), NULL);
		ms_ast_attach_chld(node, left, right);
		left = node;
	}
	return (left);
}

static t_ast	*ms_parse_and_or(t_parser *parser)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*node;

	left = ms_parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (parser->current
		&& (parser->current->type == TOKEN_AND_IF
			|| parser->current->type == TOKEN_OR_IF))
	{
		if (parser->current->type == TOKEN_OR_IF)
			node = ms_ast_new(NODE_OR);
		else
			node = ms_ast_new(NODE_AND);
		ms_parser_consume(parser, parser->current->type);
		right = ms_parse_pipeline(parser);
		if (!right)
			return (ms_ast_clear(&left), NULL);
		if (!node)
			return (ms_ast_clear(&left), ms_ast_clear(&right), NULL);
		ms_ast_attach_chld(node, left, right);
		left = node;
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
