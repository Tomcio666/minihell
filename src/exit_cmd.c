/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:12:10 by tloin             #+#    #+#             */
/*   Updated: 2026/03/04 17:53:11 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	exit_bad_arg(const char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

static void	exit_do(t_shell *shell, int status)
{
	shell->exit_status = status;
	shell->exit_requested = 1;
}

int	exit_cmd(t_shell *shell, t_simple_cmd *cmd)
{
	int		status;
	char	**argv;

	argv = NULL;
	if (cmd && cmd->argv && cmd->argv[1])
		argv = cmd->argv;
	if (argv && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (argv && !ft_is_numeric(argv[1]))
	{
		exit_do(shell, exit_bad_arg(argv[1]));
		return (2);
	}
	if (argv)
		status = ft_atoi(argv[1]) & 0xFF;
	else
		status = shell->last_status;
	exit_do(shell, status);
	return (status);
}
