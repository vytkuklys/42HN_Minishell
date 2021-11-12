/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 00:01:27 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/04 15:27:44 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dollar(char *cmd_line, int index)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (cmd_line[i] != '\0' && i < index)
	{
		if ((cmd_line[i] == '"' || cmd_line[i] == '\'')
			&& !is_char_escaped(cmd_line, i))
			quotes++;
		i++;
	}
	if (quotes % 2 == 0 && (cmd_line[index + 1] == '"' \
		|| cmd_line[index + 1] == '\''))
		return (0);
	return (1);
}

char
	*get_text_outside_quotes(char *cmd_line, int *index, int len, char **env)
{
	int		i;
	int		j;
	char	*text;

	if (cmd_line == NULL)
		return (NULL);
	text = ft_calloc(ft_strlen(cmd_line) + 1, 1);
	if (text == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_line[i] != '\0' && i < len)
	{
		i += add_char_to_text(&text, cmd_line, &j, i) + 1;
	}
	(*index) += i;
	if (!env)
		env = NULL;
	expand_variable(&text, env, '"', cmd_line);
	return (text);
}

char	*get_text_in_quotes(char *s, int *index, char **env)
{
	int		i;
	int		j;
	char	*quote;

	quote = ft_calloc(ft_strlen(s), 1);
	if (quote == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == '\\')
			i += add_slashes(&quote, &s[i], &j, s[0]) - 1;
		else if (s[i] == s[0] && ((is_char_escaped(s, i) && \
			are_slashes_even(s, i)) || (!is_char_escaped(s, i))))
			break ;
		else if (!(s[i] == s[0] && !is_char_escaped(s, i)))
		{
			quote[j] = s[i];
			j++;
		}
	}
	expand_variable(&quote, env, s[0], s);
	(*index) = *index + i + 1;
	return (quote);
}

char	*get_arg(char *cmd_line, int len, char **env)
{
	int		i;
	char	*arg;
	char	*tmp;
	int		expanded;

	expanded = get_exp_arg_len(cmd_line, env, len);
	arg = ft_calloc(1, 1);
	if (arg == NULL)
		return (NULL);
	i = 0;
	while (cmd_line && cmd_line[i] != '\0' && i < len)
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
			tmp = get_text_in_quotes(&cmd_line[i], &i, env);
		else
			tmp = get_text_outside_quotes(&cmd_line[i], &i, len - i, env);
		arg = ft_strjoin(&arg, tmp);
		free(tmp);
		tmp = NULL;
		if (arg == NULL)
			return (NULL);
	}
	if (cmd_line[0] == '"' || cmd_line[0] == '\'')
		arg = trim_back(arg, expanded);
	return (arg);
}

int	get_argv(char *cmd_line, char **argv, char **env)
{
	int	i;
	int	j;
	int	len;
	int	strlenn;

	strlenn = ft_strlen(cmd_line);
	i = 0;
	j = 0;
	while (cmd_line[i] != '\0' && strlenn > i)
	{
		len = 0;
		if (cmd_line[i] != ' ')
		{
			len = get_arg_len(&cmd_line[i]);
			argv[j] = get_arg(&cmd_line[i], len, env);
			if (argv[j] == NULL)
				return (-1);
			j++;
			i += len;
		}
		else
			i++;
	}
	argv[j] = NULL;
	return (0);
}
