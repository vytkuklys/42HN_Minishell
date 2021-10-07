/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:38:51 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/06 17:15:07 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_char_escaped(char *cmd_line, int i)
{
	if (i == 0)
		return (0);
	else if (i > 0 && cmd_line[i - 1] != '\\')
		return (0);
	return (1);
}

int exists_pipes(char *cmd_line)
{
	char	quote;
	int		i;
	int		pipes;

	quote = '\0';
	i = 0;
	pipes = 0;
	while (cmd_line[i] != '\0')
	{
		if (!quote && cmd_line[i] == '|' && !is_char_escaped(cmd_line, i))
			pipes++;
		if (!quote && (cmd_line[i] == '\'' || cmd_line[i] == '"'))
			quote = cmd_line[i];
		else if (quote && cmd_line[i] == quote && !is_char_escaped(cmd_line, i))
			quote = '\0';
		i++;
	}
	return (pipes);
}

int are_slashes_even(char *cmd_line, int i)
{
	int	slashes;

	slashes = 0;
	while (i > 0)
	{
		i--;
		if (cmd_line[i] == '\\')
			slashes++;
	}
	return (slashes % 2 == 0);
}

int are_quotes_valid(char *cmd_line)
{
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	while (cmd_line[i] != '\0')
	{
		if (!quote && (cmd_line[i] == '\'' || cmd_line[i] == '"') && !is_char_escaped(cmd_line, i))
			quote = cmd_line[i];
		else if (quote && cmd_line[i] == quote && !is_char_escaped(cmd_line, i))
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
	return (0);
}

int are_slashes_valid(char *cmd_line)
{
	char	quote;
	int		i;
	int		j;

	quote = '\0';
	i = 0;
	while (cmd_line && cmd_line[i] != '\0')
	{
		j = 0;
		if (!quote && cmd_line[i] == '\\')
		{
			while (cmd_line[i + j] == '\\')
				j++;
			if ((j % 2 == 1 && ft_strchr(" \0", cmd_line[i + j])))
				return (0);
			else if (j % 2 == 0 && ft_strchr("\"'", cmd_line[i + j]) && cmd_line[i + j] != '\0')
				return (0);
		}
		if (!quote && (cmd_line[i] == '\'' || cmd_line[i] == '"'))
			quote = cmd_line[i];
		else if (quote && cmd_line[i] == quote && !is_char_escaped(cmd_line, i))
			quote = '\0';
		i+= 1 + j;
	}
	return (1);
}

// int main(int argc, char **argv)
// {
//     printf("%d", are_slashes_valid("\\\\'"));
//     if (argv == NULL)
//         return (1);
//     return (0);
// }