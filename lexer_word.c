/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tloin <tloin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:15:00 by tloin             #+#    #+#             */
/*   Updated: 2026/01/20 19:56:03 by tloin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*ms_append_char(char *s, char c)
{
	char	*new_str;
	size_t	len;

	len = 0;
	if (s)
		len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	if (s)
		ft_memcpy(new_str, s, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}

static char	*ms_append_str(char *s, const char *add)
{
	char	*new_str;
	size_t	len;
	size_t	add_len;

	if (!add)
		return (s);
	len = 0;
	if (s)
		len = ft_strlen(s);
	add_len = ft_strlen(add);
	new_str = malloc(sizeof(char) * (len + add_len + 1));
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	if (s)
		ft_memcpy(new_str, s, len);
	ft_memcpy(new_str + len, add, add_len);
	new_str[len + add_len] = '\0';
	free(s);
	return (new_str);
}

static int	ms_is_name_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	ms_is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	ms_expand_status(char **out, t_shell *shell)
{
	char	*status;
	int		value;

	value = 0;
	if (shell)
		value = shell->last_status;
	status = ft_itoa(value);
	if (!status)
		return (-1);
	*out = ms_append_str(*out, status);
	free(status);
	if (!*out)
		return (-1);
	return (0);
}

static int	ms_append_dollar(char **out)
{
	*out = ms_append_char(*out, '$');
	if (!*out)
		return (-1);
	return (0);
}

static int	ms_expand_var(const char *s, int i, char **out, t_shell *shell)
{
	int		start;
	char	*name;
	char	**slot;

	if (!s[i])
	{
		if (ms_append_dollar(out) != 0)
			return (-1);
		return (i);
	}
	if (s[i] == '?')
	{
		if (ms_expand_status(out, shell) != 0)
			return (-1);
		return (i + 1);
	}
	if (!ms_is_name_start(s[i]))
	{
		if (ms_append_dollar(out) != 0)
			return (-1);
		return (i);
	}
	start = i;
	while (s[i] && ms_is_name_char(s[i]))
		i++;
	name = ft_substr(s, start, i - start);
	if (!name)
		return (-1);
	slot = get_env(name, shell);
	if (slot)
		*out = ms_append_str(*out, trim_env(*slot));
	free(name);
	if (!*out)
		return (-1);
	return (i);
}

static int	ms_read_quote(const char *s, int i, char quote,
				char **out, t_shell *shell)
{
	while (s[i] && s[i] != quote)
	{
		if (quote == '"' && s[i] == '$')
		{
			i = ms_expand_var(s, i + 1, out, shell);
			if (i < 0)
				return (-1);
		}
		else
		{
			*out = ms_append_char(*out, s[i]);
			if (!*out)
				return (-1);
			i++;
		}
	}
	if (!s[i])
		return (-1);
	return (i + 1);
}

int	ms_read_word(const char *s, int i, char **out, t_shell *shell)
{
	char	quote;

	while (s[i] && !ms_is_space(s[i]) && !ms_is_operator(s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			i = ms_read_quote(s, i + 1, quote, out, shell);
			if (i < 0)
				return (-1);
		}
		else if (s[i] == '$')
		{
			i = ms_expand_var(s, i + 1, out, shell);
			if (i < 0)
				return (-1);
		}
		else
		{
			*out = ms_append_char(*out, s[i]);
			if (!*out)
				return (-1);
			i++;
		}
	}
	return (i);
}
