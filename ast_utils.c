/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 11:14:48 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ms_ast_new(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->command = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ms_ast_attach_children(t_ast *parent, t_ast *left, t_ast *right)
{
	if (!parent)
		return ;
	parent->left = left;
	parent->right = right;
}

void	ms_ast_set_command(t_ast *node, t_simple_cmd *command)
{
	if (!node)
		return ;
	node->command = command;
}

void	ms_ast_clear(t_ast **node)
{
	if (!node || !*node)
		return ;
	if ((*node)->left)
		ms_ast_clear(&(*node)->left);
	if ((*node)->right)
		ms_ast_clear(&(*node)->right);
	if ((*node)->command)
		ms_simple_cmd_clear(&(*node)->command);
	free(*node);
	*node = NULL;
}
