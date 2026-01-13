/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:14 by tloin             #+#    #+#             */
/*   Updated: 2026/01/13 19:13:16 by tloin            ###   ########.fr       */
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

	while (1)
	{
		if (print_prompt(&prompt) != 0)
			return (1);
		buffer = readline(prompt);
		free(prompt);
		if (!buffer)
			continue ;
		if (ft_strncmp(buffer, "pwd", 4) == 0 && buffer[3] == '\0')
			pwd_command();
		else
			printf("%s\n", buffer);
		free(buffer);
	}
	return (0);
}
