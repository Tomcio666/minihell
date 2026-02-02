/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/02 17:54:52 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include "ms_types.h"

int	pwd_command(void);
int	cd_cmd(t_shell *shell, t_simple_cmd *cmd);
int	echo_cmd(t_simple_cmd *cmd);
int	env_cmd(t_shell *shell, t_simple_cmd *cmd);
int	export_cmd(t_shell *shell, t_simple_cmd *cmd);
int	unset_cmd(t_shell *shell, t_simple_cmd *cmd);
int	exit_cmd(t_shell *shell, t_simple_cmd *cmd);

#endif
