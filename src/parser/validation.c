/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:38:51 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/01 14:08:50 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_char_escaped(char *cmd_line, int i)
{
	if (i == 0)
		return (0);
	else if (i > 0 && cmd_line[i - 1] != '\\')
		return (0);
	return (1);
}

int	exists_pipes(char *cmd_line)
{
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	while (cmd_line[i] != '\0')
	{
		if (!quote && cmd_line[i] == '|' && !is_char_escaped(cmd_line, i))
			return (1);
		if (!quote && (cmd_line[i] == '\'' || cmd_line[i] == '"'))
			quote = cmd_line[i];
		else if (quote && cmd_line[i] == quote && !is_char_escaped(cmd_line, i))
			quote = '\0';
		i++;
	}
	return (0);
}

int	are_slashes_even(char *cmd_line, int i)
{
	int	slashes;

	slashes = 0;
	while (i > 0 && cmd_line[i - 1] == '\\')
	{
		i--;
		slashes++;
	}
	return (slashes % 2 == 0);
}

int	are_quotes_valid(char *cmd_line, t_var **data)
{
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	while (cmd_line[i] != '\0')
	{
		if (!quote && (cmd_line[i] == '\'' || cmd_line[i] == '"')
			&& (!is_char_escaped(cmd_line, i) || are_slashes_even(cmd_line, i)))
			quote = cmd_line[i];
		else if (quote && cmd_line[i] == quote \
			&& (!is_char_escaped(cmd_line, i) || are_slashes_even(cmd_line, i)))
			quote = '\0';
		else if (quote && cmd_line[i] == quote && is_char_escaped(cmd_line, i))
		{
			if (are_slashes_even(cmd_line, i))
				quote = '\0';
		}
		i++;
	}
	if (quote == '\0')
		return (1);
	return (throw_invalid_error(data));
}

int	are_slashes_valid(char *s, t_var **data)
{
	char	quote;
	int		i[2];

	quote = '\0';
	i[0] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = 0;
		if (!quote && s[i[0]] == '\\')
		{
			while (s[i[0] + i[1]] == '\\')
				i[1]++;
			if ((i[1] % 2 == 1 && ft_strchr(" \0", s[i[0] + i[1]])))
				return (throw_invalid_error(data));
		}
		if (!quote && (s[i[0]] == '\'' || s[i[0]] == '"'))
			quote = s[i[0]];
		else if (quote && s[i[0]] == quote && !is_char_escaped(s, i[0]))
			quote = '\0';
		i[0] += 1 + i[1];
	}
	return (1);
}
