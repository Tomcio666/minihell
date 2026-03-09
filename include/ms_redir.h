/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/03/09 16:52:10 by tloin            ###   ########.fr       */
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
int		ms_setup_heredoc_stdin(void);
int		ms_restore_stdin_on_error(int save_in);
int		ms_cleanup_heredoc_error(int *pipefd);
int		ms_process_heredoc_line(char *line, const char *delim, int *pipefd);

#endif
