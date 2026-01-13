/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:10 by tloin             #+#    #+#             */
/*   Updated: 2026/01/13 19:11:40 by tloin            ###   ########.fr       */
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

int	pwd_command(void);

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

#endif

