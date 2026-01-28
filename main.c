/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:14 by tloin             #+#    #+#             */
/*   Updated: 2026/01/28 16:42:37 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static volatile sig_atomic_t	g_signal;

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
	free(path);
	return (display);
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

static int	print_prompt(t_shell *shell, char **prompt)
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

static void	ms_sigint_handler(int sig)
{
	(void)sig;
	if (rl_readline_state & RL_STATE_READCMD)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
	}
}

static void	ms_sigquit_handler(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
	if (rl_readline_state & RL_STATE_READCMD)
	{
		rl_on_new_line();
		rl_replace_line("  ", 2);
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ms_signals_setup(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ms_sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = ms_sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(void)
{
	char	*buffer;
	char	*prompt;
	t_token	*tokens;
	t_ast	*ast;
	t_shell	shell;

	shell.env = NULL;
	shell.user = NULL;
	shell.last_status = 0;
	load_env(&shell);
	g_signal = 0;
	ms_signals_setup();

	while (1)
	{
		if (print_prompt(&shell, &prompt) != 0)
			return (1);
		buffer = readline(prompt);
		rl_readline_state &= ~RL_STATE_READCMD;
		free(prompt);
		if (buffer == NULL)
			exit(0);
		if (g_signal == SIGINT)
		{
			shell.last_status = 130;
			g_signal = 0;
			free(buffer);
			continue ;
		}
		if (*buffer)
			add_history(buffer);
		else
		{
			free(buffer);
			continue ;
		}
		tokens = ms_lexer(buffer, &shell);
		if (tokens)
		{
			ast = ms_parse(tokens);
			if (ast)
			{
				shell.last_status = ms_execute_ast(ast, &shell);
				ms_ast_clear(&ast);
			}
			ms_token_clear(&tokens);
		}
		free(buffer);
	}
	local_env_clear(&shell);
	return (0);
}
