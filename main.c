/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:14 by tloin             #+#    #+#             */
/*   Updated: 2026/01/21 18:30:20 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

void	handle_sigint(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (sig == 3)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	printf("\n%d", sig);
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);

	while (1)
	{
		if (print_prompt(&shell, &prompt) != 0)
			return (1);
		buffer = readline(prompt);
		free(prompt);
		if (buffer == NULL)
			exit(0);
		if (!buffer)
			continue ;
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
