/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:47:13 by tloin             #+#    #+#             */
/*   Updated: 2026/01/14 18:51:40 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir *ms_redir_new(t_redir_type type, char *word)
{
	t_redir *node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->kind = type;
	node->word = word;
	node->next = NULL;
	return (node);
}
void ms_redir_add_back(t_redir **list, t_redir *new_node)
{
	t_redir *last;
	
	if (!list || !new_node)
		return ;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}
void ms_redir_clear(t_redir **list)
{
	t_redir *node;
	t_redir *next;

	if (!list)
		return ;
	node = *list;
	while (node)
	{
		next = node->next;
		free(node->word);
		free(node);
		node = next;
	}
	*list = NULL;
}
t_simple_cmd *ms_simple_cmd_new(void)
{
	t_simple_cmd *cmd;

	cmd = malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	return (cmd);
}
void ms_simple_cmd_clear(t_simple_cmd **cmd)
{
	int index;

	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->argv)
	{
		index = 0;
		while ((*cmd)->argv[index])
		{
			free((*cmd)->argv[index]);
			index++;
		}
		free((*cmd)->argv);
	}
	ms_redir_clear(&(*cmd)->redir);
	free(*cmd);
	*cmd = NULL;
}
