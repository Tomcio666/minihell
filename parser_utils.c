/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:40:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 11:14:48 by tloin            ###   ########.fr       */
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

static char	**ms_argv_add(char **argv, const char *value)
{
	char	**new_argv;
	int		count;
	int		index;

	count = 0;
	while (argv && argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	index = 0;
	while (index < count)
	{
		new_argv[index] = argv[index];
		index++;
	}
	new_argv[index] = ft_strdup(value);
	if (!new_argv[index])
	{
		free(new_argv);
		return (NULL);
	}
	new_argv[index + 1] = NULL;
	free(argv);
	return (new_argv);
}

int	ms_parser_add_arg(t_simple_cmd *cmd, const char *value)
{
	char	**new_argv;

	if (!cmd)
		return (0);
	new_argv = ms_argv_add(cmd->argv, value);
	if (!new_argv)
		return (0);
	cmd->argv = new_argv;
	return (1);
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

int	ms_parser_is_redir(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (1);
	if (type == TOKEN_REDIR_OUT)
		return (1);
	if (type == TOKEN_REDIR_APPEND)
		return (1);
	if (type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	ms_parser_token_is_word_or_redir(t_token_type type)
{
	if (type == TOKEN_WORD)
		return (1);
	return (ms_parser_is_redir(type));
}
