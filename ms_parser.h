/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:59:08 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSER_H
# define MS_PARSER_H

# include "ms_types.h"

t_ast			*ms_parse(t_token *tokens);

t_simple_cmd	*ms_parse_simple_cmd(t_parser *parser);
int				ms_parser_add_arg(t_simple_cmd *cmd, const char *value);
int				ms_parser_expect_word(t_parser *parser, char **out);
int				ms_parser_consume(t_parser *parser, t_token_type type);
int				ms_parser_is_redir(t_token_type type);
int				ms_parser_token_is_word_or_redir(t_token_type type);

#endif
