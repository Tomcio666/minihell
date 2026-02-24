/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:41:50 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/02 16:46:25 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_has_slash(const char *s)
{
	int	index;

	index = 0;
	while (s && s[index])
	{
		if (s[index] == '/')
			return (1);
		index++;
	}
	return (0);
}

void	ms_free_split(char **arr)
{
	int	index;

	if (!arr)
		return ;
	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

char	**ms_env_path(t_shell *shell)
{
	char	**slot;
	char	*value;

	slot = get_env("PATH", shell);
	if (!slot)
		return (NULL);
	value = trim_env(*slot);
	if (!value)
		return (NULL);
	return (ft_split(value, ':'));
}

char	*ms_path_join(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

int	ms_exec_search(t_simple_cmd *cmd, t_shell *shell)
{
	char	**paths;
	char	*full;
	int		index;

	paths = ms_env_path(shell);
	if (!paths)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (127);
	}
	index = 0;
	while (paths[index])
	{
		full = ms_path_join(paths[index], cmd->argv[0]);
		if (!full)
			return (ms_free_split(paths), 1);
		if (access(full, X_OK) == 0)
			return (execute_executable(full, cmd->argv, shell));
		free(full);
		index++;
	}
	ms_free_split(paths);
	ft_putstr_fd("minishell: command not found\n", 2);
	return (127);
}
