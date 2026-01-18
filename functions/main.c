/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:59:26 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/17 19:46:40 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_shell	s_shell;

	s_shell.env = NULL;
	load_env(&s_shell);
	s_shell.user = *(get_env("USER", &s_shell));
	printf("%s\n", *(get_env("USER", &s_shell)));
	unset_cmd(get_env("USER", &s_shell));
	printf("%s\n", s_shell.user);
	export_cmd(&s_shell);
	local_env_clear(&s_shell);
	return (0);
}
