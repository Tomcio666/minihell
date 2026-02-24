/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:05:00 by tloin             #+#    #+#             */
/*   Updated: 2026/02/10 16:28:19 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H

# include "ms_types.h"

char	*trim_env(char *env);
void	local_env_clear(t_shell *shell);
void	load_env(t_shell *shell);
char	**get_env(const char *name, t_shell *shell);
int		ms_env_set(t_shell *shell, const char *name, const char *value);
int		ms_env_unset(t_shell *shell, const char *name);
char	*ms_env_join(const char *name, const char *value);
t_shell	sort_env(t_shell sorted);

#endif
