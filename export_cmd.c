/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:38:54 by mgumienn          #+#    #+#             */
/*   Updated: 2026/01/28 15:27:38 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_is_valid_name(const char *s)
{
	int	index;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	index = 1;
	while (s[index] && s[index] != '=')
	{
		if (!ft_isalnum(s[index]) && s[index] != '_')
			return (0);
		index++;
	}
	return (1);
}

static void	ms_export_print_one(char *entry)
{
	int	index;

	if (!ft_strchr(entry, '='))
	{
		printf("declare -x %s\n", entry);
		return ;
	}
	printf("declare -x ");
	index = 0;
	while (entry[index] && entry[index] != '=')
		printf("%c", entry[index++]);
	printf("=\"%s\"\n", trim_env(entry));
}

static int	ms_export_assign(t_shell *shell, char *arg)
{
	char	*equal;
	char	*name;
	int		status;
	char	**slot;

	if (!ms_is_valid_name(arg))
		return (ft_putstr_fd("export: not valid\n", 2), 1);
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		slot = get_env(arg, shell);
		if (slot)
			return (0);
		return (ms_env_set(shell, arg, ""), 0);
	}
	name = ft_substr(arg, 0, equal - arg);
	if (!name)
		return (1);
	status = ms_env_set(shell, name, equal + 1);
	free(name);
	if (status == 1)
		return (0);
	return (1);
}

int	export_cmd(t_shell *shell, t_simple_cmd *cmd)
{
	int	index;
	int	status;

	if (!shell || !shell->env)
		return (1);
	if (!cmd || !cmd->argv || !cmd->argv[1])
	{
		index = 0;
		while (shell->env[index])
			ms_export_print_one(shell->env[index++]);
		return (0);
	}
	index = 1;
	status = 0;
	while (cmd->argv[index])
	{
		if (ms_export_assign(shell, cmd->argv[index]))
			status = 1;
		index++;
	}
	return (status);
}
