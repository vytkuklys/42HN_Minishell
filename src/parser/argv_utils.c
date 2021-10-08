/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:58:36 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/08 00:11:46 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_arg_len(char *cmd_line)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (cmd_line[i] != '\0' && !ft_strchr(";| ", cmd_line[i]))
	{
		if (ft_strchr("'\"", cmd_line[i]))
			len += get_end_of_quote_pos(&cmd_line[i]) + 1;
		else
			len += get_end_of_arg_pos(&cmd_line[i]);
		i += len;
	}
	return (len);
}

int add_char_to_text(char **str, char *cmd_line, int *j, int i)
{
	int whitespace;

	whitespace = 0;
	if (cmd_line && cmd_line[i] == '\\')
		return (add_slashes(str, &cmd_line[i], j) - 1);
	if (cmd_line && cmd_line[i] == ' ')
	{
		(*str)[*j] = cmd_line[i];
		whitespace += get_whitespace(cmd_line + i + 1);
		(*j)++;
	}	
	else if (cmd_line && cmd_line[i])
	{
		if (cmd_line[i] != '"' && cmd_line[i] != '\'')
		{
			(*str)[*j] = cmd_line[i];
			(*j)++;
		}
		else if (is_char_escaped(cmd_line, i) && !are_slashes_even(cmd_line, i))
		{
			(*str)[*j] = cmd_line[i];
			(*j)++;
		}
	}
	return (whitespace);
}

char	get_whitespace_char(char c, int slashes)
{
	float coefficient;

	coefficient = (float)slashes / 4;
	coefficient = coefficient - (int)coefficient;
	if (coefficient < 0.5 || !ft_strchr("tvfrbn", c))
		return ('\0');
	if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == 'f')
		return ('\f');
	else if (c == 'r')
		return ('\r');
	else if (c == 'b')
		return ('\b');
	else if (c == 'n')
		return ('\n');
	return ('\0');
}

int round_num(float num)
{
	if (num - (int)num >= 0.5)
		return ((int)num + 1);
	return ((int)num);
}

int add_slashes(char **quote, char *start, int *j)
{
	int		i;
	int		slashes;

	if (start == NULL || *quote == NULL) //add clean exit / free stuff
		return (-1);
	i = 0;
	while (start && start[i] == '\\')
		i++;
	slashes = round_num((float)i / 4);
	if (get_whitespace_char(start[i], i))
		slashes -= 1;
	while (slashes > 0)
	{
		(*quote)[(*j)] = '\\';
		(*j)++;
		slashes--;
	}
	if (get_whitespace_char(start[i], i))
	{
		(*quote)[(*j)] = get_whitespace_char(start[i], i);
		(*j)++;
		i += 1;
	}
	return (i);
}
