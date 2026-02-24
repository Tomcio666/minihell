/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:54:52 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_AST_H
# define MS_AST_H

# include "ms_types.h"

t_ast	*ms_ast_new(t_node_type type);
void	ms_ast_attach_chld(t_ast *parent, t_ast *left, t_ast *right);
void	ms_ast_set_command(t_ast *node, t_simple_cmd *command);
void	ms_ast_clear(t_ast **node);

#endif
