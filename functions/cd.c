/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:30:40 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/14 17:54:12 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_cmd(char *path)
{
	struct stat	buffer;

	if (chdir(path) == 0)
		return (getcwd(NULL, 0));
	perror("cd");
	return (NULL);
}
