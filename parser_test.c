/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/20 19:56:03 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_token	*list;
	t_ast	*ast;
	char	*input;
	t_shell	shell;

	input = "(echo hi | grep h) && pwd";
	shell.env = NULL;
	shell.user = NULL;
	shell.last_status = 0;
	list = ms_lexer(input, &shell);
	if (!list)
		return (1);
	ast = ms_parse(list);
	if (!ast)
	{
		ms_token_clear(&list);
		return (1);
	}
	printf("parse ok\n");
	ms_ast_clear(&ast);
	ms_token_clear(&list);
	return (0);
}
