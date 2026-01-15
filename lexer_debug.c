/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:01:46 by tloin             #+#    #+#             */
/*   Updated: 2026/01/15 19:27:50 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*g_token_labels[TOKEN_END + 1] =
{
	"WORD",
	"PIPE",
	"AND_IF",
	"OR_IF",
	"REDIR_IN",
	"REDIR_OUT",
	"REDIR_APPEND",
	"HEREDOC",
	"LPAREN",
	"RPAREN",
	"END"
};

const char	*ms_token_type_name(t_token_type type)
{
	if (type < 0 || type > TOKEN_END)
		return ("UNKNOWN");
	return (g_token_labels[type]);
}

void	ms_token_debug_print(t_token *list)
{
	t_token	*node;

	node = list;
	while (node)
	{
		if (node->value)
			printf("token %-12s : %s\n",
				ms_token_type_name(node->type), node->value);
		else
			printf("token %-12s\n", ms_token_type_name(node->type));
		node = node->next;
	}
	printf("token %-12s\n", ms_token_type_name(TOKEN_END));
}
