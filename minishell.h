/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:10 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 11:27:09 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>

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
	char			**argv;
	t_redir			*redir;
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
}	t_shell;

typedef struct s_parser
{
	t_token	*current;
}t_parser;

t_token			*ms_token_new(t_token_type type, const char *value);
void			ms_token_add_back(t_token **list, t_token *new_node);
void			ms_token_clear(t_token **list);
const char		*ms_token_type_name(t_token_type type);
void			ms_token_debug_print(t_token *list);

t_redir			*ms_redir_new(t_redir_type type, char *word);
void			ms_redir_add_back(t_redir **list, t_redir *new_node);
void			ms_redir_clear(t_redir **list);

t_simple_cmd	*ms_simple_cmd_new(void);
void			ms_simple_cmd_clear(t_simple_cmd **cmd);

t_ast			*ms_ast_new(t_node_type type);
void			ms_ast_attach_children(t_ast *parent, t_ast *left, t_ast *right);
void			ms_ast_set_command(t_ast *node, t_simple_cmd *command);
void			ms_ast_clear(t_ast **node);

int				pwd_command(void);

t_token			*ms_lexer(const char *input);
int				ms_is_space(char c);
int				ms_is_operator(char c);
int				ms_read_word(const char *s, int i, char **out);
int				ms_operator_advance(const char *s, int i, t_token_type *type);

t_ast			*ms_parse(t_token *tokens);
t_simple_cmd	*ms_parse_simple_cmd(t_parser *parser);
int				ms_parser_add_arg(t_simple_cmd *cmd, const char *value);
int				ms_parser_expect_word(t_parser *parser, char **out);
int				ms_parser_consume(t_parser *parser, t_token_type type);
int				ms_parser_is_redir(t_token_type type);
int				ms_parser_token_is_word_or_redir(t_token_type type);

int				ms_execute_ast(t_ast *node);

#endif
