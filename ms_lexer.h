/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:54:52 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H

# include "ms_types.h"

t_token	*ms_lexer(const char *input, t_shell *shell);
int		ms_is_space(char c);
int		ms_is_operator(char c);
int		ms_read_word(t_lex_state st, int i);
int		ms_operator_advance(const char *s, int i, t_token_type *type);
char	*ms_append_char(char *s, char c);
char	*ms_append_str(char *s, const char *add);
int		ms_expand_status(t_lex_state *st);
int		ms_append_dollar(t_lex_state *st);
int		ms_expand_var_cases(t_lex_state *st, int i);

#endif
