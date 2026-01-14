/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:41:36 by tloin             #+#    #+#             */
/*   Updated: 2026/01/14 18:59:25 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ms_token_new(t_token_type type, char *value) 
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}
void ms_token_add_back(t_token **list, t_token *new_node)
{
	t_token *last;
	
	if (!list || !new_node)
		return ;
	if (*list)
		return (*list = new_node);
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}
void ms_token_clear(t_token **list)
{
	t_token *node;
	t_token *next;

	if (!list)
		return ;
	node = *list;
	while (node)
	{
		next = node->next;
		free(node->value);
		free(node);
		node = next;
	}
	*list = NULL;
}
