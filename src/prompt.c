/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:12:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 16:48:26 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_env_value(t_shell *shell, const char *name)
{
	char	**slot;

	if (!shell || !name)
		return (NULL);
	slot = get_env(name, shell);
	if (!slot)
		return (NULL);
	return (trim_env(*slot));
}

static char	*ms_prompt_path(t_shell *shell)
{
	char	*path;
	char	*home;
	char	*display;
	int		len;
	char	*pwd;

	pwd = ms_env_value(shell, "PWD");
	path = NULL;
	if (pwd)
		path = ft_strdup(pwd);
	if (!path)
		path = getcwd(NULL, 0);
	if (!path)
		return (ft_strdup("?"));
	home = ms_env_value(shell, "HOME");
	if (!home)
		return (path);
	len = (int)ft_strlen(home);
	if (ft_strncmp(path, home, len) != 0)
		return (path);
	if (path[len] == '\0')
		display = ft_strdup("~");
	else
		display = ft_strjoin("~", path + len);
	return (free(path), display);
}

static char	*ms_prompt_join(const char *user, const char *path)
{
	char	*tmp;
	char	*prompt;

	tmp = ft_strjoin(user, ":");
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, path);
	free(tmp);
	if (!prompt)
		return (NULL);
	tmp = ft_strjoin(prompt, "$ ");
	free(prompt);
	return (tmp);
}

int	print_prompt(t_shell *shell, char **prompt)
{
	const char	*user;
	char		*path;

	user = ms_env_value(shell, "USER");
	if (!user)
		user = "minishell";
	path = ms_prompt_path(shell);
	if (!path)
		return (perror("minishell"), 1);
	*prompt = ms_prompt_join(user, path);
	free(path);
	if (!*prompt)
		return (perror("minishell"), 1);
	return (0);
}
