/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:10 by tloin             #+#    #+#             */
/*   Updated: 2026/01/14 18:58:13 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "stdbool.h"

typedef enum e_token_type // Token types for lexer part
{
	TOKEN_WORD, // "command or argument"
	TOKEN_PIPE, // |
	TOKEN_AND_IF, // &&
	TOKEN_OR_IF, // ||
	TOKEN_REDIR_IN, // <
	TOKEN_REDIR_OUT, // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_LPAREN, // (
	TOKEN_RPAREN, // )
	TOKEN_END // ;
}	t_token_type;

typedef enum e_redir_type // Redirection types
{
	REDIR_IN, // <
	REDIR_OUT, // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC // <<
}	t_redir_type;

typedef enum e_node_type // AST node types
{
	NODE_SIMPLE_CMD, // simple command
	NODE_PIPE, // |
	NODE_AND, // &&
	NODE_OR, // ||
	NODE_SUBSHELL // ( )
}	t_node_type;

typedef struct s_token // Token structure for lexer part
{
	t_token_type	type; // type of the token
	char			*value; // value of the token
	struct s_token	*next; // pointer to the next token
}	t_token;

typedef struct s_redir // Redirection structure
{
	t_redir_type	kind; // type of the redirection
	char			*word; // target file or delimiter
	struct s_redir	*next; // pointer to the next redirection
}	t_redir;

typedef struct s_simple_cmd // Simple command structure
{
	char			**argv; // argument vector
	t_redir			*redir; // linked list of redirections
}	t_simple_cmd;

typedef struct s_ast // AST node structure
{
	t_node_type		type; // type of the AST node
	t_simple_cmd	*command; // simple command (if applicable)
	struct s_ast	*left; // left child
	struct s_ast	*right; // right child
}	t_ast;

typedef struct s_cmd // Command structure for execution part
{
	char			**argv; // argument vector
	char			*name; // command name
	int				index; // command index in the pipeline
	struct s_cmd	*next; // pointer to the next command
}	t_cmd;

typedef struct s_shell // Main shell structure
{
	char	**env; // environment variables
	char	*user; // current user
}	t_shell;

int			pwd_command(void); // Example function prototype
t_token		*ms_token_new(t_token_type type, char *value); // Create a new token
void		ms_token_add_back(t_token **list, t_token *new_node); // Add token to the end of the list
void		ms_token_clear(t_token **list); // Clear the token list
t_redir		*ms_redir_new(t_redir_type type, char *word); // Create a new redirection
void		ms_redir_add_back(t_redir **list, t_redir *new_node); // Add redirection to the end of the list
void		ms_redir_clear(t_redir **list); // Clear the redirection list
t_simple_cmd	*ms_simple_cmd_new(void); // Create a new simple command
void		ms_simple_cmd_clear(t_simple_cmd **cmd); // Clear the simple command
t_ast		*ms_ast_new(t_node_type type); // Create a new AST node
void		ms_ast_attach_children(t_ast *parent, t_ast *left, t_ast *right); // Attach children to AST node
void		ms_ast_set_command(t_ast *node, t_simple_cmd *command); // Set command for AST node
void		ms_ast_clear(t_ast **node); // Clear the AST

#endif