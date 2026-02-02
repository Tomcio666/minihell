/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:54:52 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_CMD_H
# define MS_CMD_H

# include "ms_types.h"

t_redir			*ms_redir_new(t_redir_type type, char *word);
void			ms_redir_add_back(t_redir **list, t_redir *new_node);
void			ms_redir_clear(t_redir **list);

t_simple_cmd	*ms_simple_cmd_new(void);
void			ms_simple_cmd_clear(t_simple_cmd **cmd);

#endif
