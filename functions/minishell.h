/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:10 by tloin             #+#    #+#             */
/*   Updated: 2026/01/17 19:46:55 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>

// struct and shi
typedef struct s_cmd
{
	char			**argv;
	char			*name;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	char	*user;
}	t_shell;

int		pwd_command(void);
int		echo_cmd(char *str, int flag);
char	*cd_cmd(char *path);
int		env_cmd(t_shell *s_shell);
void	load_env(t_shell *s_shell);
void	unset_cmd(char **env);
char	*trim_env(char *env);
void	local_env_clear(t_shell *s_shell);
char	**get_env(char *name, t_shell *s_shell);
void	load_env(t_shell *s_shell);
void	export_cmd(t_shell *s_shell);

//exit_cmd potem bo potrzebny jest clear exit

#endif
