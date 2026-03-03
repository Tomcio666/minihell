/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:04:14 by tloin             #+#    #+#             */
/*   Updated: 2026/03/03 17:06:51 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_init_shell(t_shell *shell)
{
	if (!shell)
		return (1);
	shell->env = NULL;
	shell->user = NULL;
	shell->last_status = 0;
	shell->ast = NULL;
	shell->exit_requested = 0;
	shell->exit_status = 0;
	load_env(shell);
	ms_signal_clear();
	ms_signals_setup();
	return (0);
}

static char	*ms_read_line(t_shell *shell)
{
	char	*prompt;
	char	*buffer;

	prompt = NULL;
	if (print_prompt(shell, &prompt) != 0)
		return (NULL);
	rl_on_new_line();
	buffer = readline(prompt);
	rl_readline_state &= ~RL_STATE_READCMD;
	free(prompt);
	return (buffer);
}

static void	ms_process_line(char *buffer, t_shell *shell)
{
	t_token	*tokens;

	if (!buffer)
		return ;
	if (ms_signal_get() == SIGINT)
		return (shell->last_status = 130, ms_signal_clear(), free(buffer));
	if (*buffer)
		add_history(buffer);
	else
		return (free(buffer));
	tokens = ms_lexer(buffer, shell);
	if (tokens)
		ms_process_tokens(tokens, shell);
	free(buffer);
}

static void	ms_cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	local_env_clear(shell);
	rl_clear_history();
}

int	main(void)
{
	char	*buffer;
	t_shell	shell;
	int		status;

	if (ms_init_shell(&shell) != 0)
		return (1);
	status = 0;
	while (1)
	{
		buffer = ms_read_line(&shell);
		if (buffer == NULL)
			break ;
		ms_process_line(buffer, &shell);
		if (shell.exit_requested)
		{
			status = shell.exit_status;
			break ;
		}
	}
	ms_cleanup_shell(&shell);
	if (shell.exit_requested)
		return (status);
	return (0);
}
