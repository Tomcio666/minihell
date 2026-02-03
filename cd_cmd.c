/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:30:40 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/03 17:09:49 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_cd_target(t_shell *shell, t_simple_cmd *cmd)
{
	char	**home;

	if (cmd && cmd->argv && cmd->argv[1])
		return (cmd->argv[1]);
	home = get_env("HOME", shell);
	if (!home)
		return (NULL);
	return (trim_env(*home));
}

static int	ms_cd_update_env(t_shell *shell, char *oldpwd)
{
	char	*cwd;
	int		status;

	if (!oldpwd)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(oldpwd);
		return (1);
	}
	status = ms_env_set(shell, "OLDPWD", oldpwd);
	status &= ms_env_set(shell, "PWD", cwd);
	free(cwd);
	free(oldpwd);
	if (status == 1)
		return (0);
	return (1);
}

int	cd_cmd(t_shell *shell, t_simple_cmd *cmd)
{
	char	*path;
	char	*oldpwd;

	if (!shell)
		return (1);
	if (cmd && cmd->argv && cmd->argv[1] && cmd->argv[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	path = ms_cd_target(shell, cmd);
	if (!path)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	if (oldpwd)
		return (ms_cd_update_env(shell, oldpwd));
	return (0);
}
