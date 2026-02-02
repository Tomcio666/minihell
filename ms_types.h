/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:55:27 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TYPES_H
# define MS_TYPES_H

# include "ms_includes.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_END
}	t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef enum e_node_type
{
	NODE_SIMPLE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_redir_type	kind;
	char			*word;
	struct s_redir	*next;
}	t_redir;

typedef struct s_simple_cmd
{
	char	**argv;
	t_redir	*redir;
}	t_simple_cmd;

typedef struct s_ast
{
	t_node_type		type;
	t_simple_cmd	*command;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_cmd
{
	char			**argv;
	char			*name;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	char	*user;
	int		last_status;
}	t_shell;

typedef struct s_parser
{
	t_token	*current;
}	t_parser;

typedef struct s_lex_state
{
	const char	*s;
	char		**out;
	t_shell		*shell;
}	t_lex_state;

typedef struct s_exec_ctx
{
	int		in_fd;
	int		out_fd;
	t_shell	*shell;
	int		in_child;
}	t_exec_ctx;

#endif
