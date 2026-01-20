/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:01:46 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 13:53:39 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*ms_token_type_name(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_AND_IF)
		return ("AND_IF");
	if (type == TOKEN_OR_IF)
		return ("OR_IF");
	if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOKEN_REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_LPAREN)
		return ("LPAREN");
	if (type == TOKEN_RPAREN)
		return ("RPAREN");
	if (type == TOKEN_END)
		return ("END");
	return ("UNKNOWN");
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
