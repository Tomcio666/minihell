/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:14 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 11:27:09 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	print_prompt(char **prompt)
{
	const char	*user;

	user = getenv("USER");
	if (!user)
		user = "minishell";
	*prompt = ft_strjoin(user, ":~$ ");
	if (!*prompt)
		return (perror("minishell"), 1);
	return (0);
}

int	main(void)
{
	char	*buffer;
	char	*prompt;
	t_token	*tokens;
	t_ast	*ast;

	while (1)
	{
		if (print_prompt(&prompt) != 0)
			return (1);
		buffer = readline(prompt);
		free(prompt);
		if (!buffer)
			continue ;
		tokens = ms_lexer(buffer);
		if (tokens)
		{
			ast = ms_parse(tokens);
			if (ast)
			{
				ms_execute_ast(ast);
				ms_ast_clear(&ast);
			}
			ms_token_clear(&tokens);
		}
		free(buffer);
	}
	return (0);
}
