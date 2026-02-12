/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:40:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/10 18:31:52 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**ms_argv_add(char **argv, const char *value)
{
	char	**new_argv;
	int		count;
	int		index;

	count = 0;
	while (argv && argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	index = 0;
	while (index < count)
	{
		new_argv[index] = argv[index];
		index++;
	}
	new_argv[index] = ft_strdup(value);
	if (!new_argv[index])
	{
		free(new_argv);
		return (NULL);
	}
	new_argv[index + 1] = NULL;
	free(argv);
	return (new_argv);
}

int	ms_parser_add_arg(t_simple_cmd *cmd, const char *value)
{
	if (!cmd)
		return (0);
	return (ms_wildcard_expand(cmd, value));
}

int	ms_parser_is_redir(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (1);
	if (type == TOKEN_REDIR_OUT)
		return (1);
	if (type == TOKEN_REDIR_APPEND)
		return (1);
	if (type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	ms_parser_token_is_word_or_redir(t_token_type type)
{
	if (type == TOKEN_WORD)
		return (1);
	return (ms_parser_is_redir(type));
}
