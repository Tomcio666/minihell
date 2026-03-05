/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/03/05 17:44:37 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REDIR_H
# define MS_REDIR_H

# include "ms_types.h"

int		ms_redir_apply(t_simple_cmd *cmd, int *save_in, int *save_out);
void	ms_redir_restore(int saved_in, int saved_out);
int		ms_redir_collect(t_simple_cmd *cmd, int *in_fd, int *out_fd);
int		ms_heredoc_fd(const char *delim);
void	ms_preprocess_heredoc(t_ast *root);

#endif
