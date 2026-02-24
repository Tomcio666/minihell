/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:54:52 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TOKEN_H
# define MS_TOKEN_H

# include "ms_types.h"

t_token		*ms_token_new(t_token_type type, const char *value);
void		ms_token_add_back(t_token **list, t_token *new_node);
void		ms_token_clear(t_token **list);
const char	*ms_token_type_name(t_token_type type);
void		ms_token_debug_print(t_token *list);

#endif
