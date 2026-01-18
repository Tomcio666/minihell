/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/18 11:05:43 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_token	*list;
	char	*input;

	input = "echo \"hi\" | grep h && pwd";
	list = ms_lexer(input);
	if (!list)
		return (1);
	ms_token_debug_print(list);
	ms_token_clear(&list);
	return (0);
}
