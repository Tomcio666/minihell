/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:20:00 by tloin             #+#    #+#             */
/*   Updated: 2026/03/05 17:52:56 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_preprocess_heredoc_in_cmd(t_simple_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	if (!cmd)
		return ;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->kind == REDIR_HEREDOC)
		{
			fd = ms_heredoc_fd(redir->word);
			if (fd >= 0)
			{
				free(redir->word);
				redir->word = ft_itoa(fd);
				redir->kind = REDIR_HEREDOC_FD;
			}
		}
		redir = redir->next;
	}
}

static void	ms_preprocess_heredoc_tree(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_SIMPLE_CMD && node->command)
		ms_preprocess_heredoc_in_cmd(node->command);
	ms_preprocess_heredoc_tree(node->left);
	ms_preprocess_heredoc_tree(node->right);
}

void	ms_preprocess_heredoc(t_ast *root)
{
	ms_preprocess_heredoc_tree(root);
}
