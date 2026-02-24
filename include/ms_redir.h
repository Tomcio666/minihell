/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:54:52 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REDIR_H
# define MS_REDIR_H

# include "ms_types.h"

int		ms_redir_apply(t_simple_cmd *cmd, int *save_in, int *save_out);
void	ms_redir_restore(int saved_in, int saved_out);
int		ms_redir_collect(t_simple_cmd *cmd, int *in_fd, int *out_fd);

#endif
