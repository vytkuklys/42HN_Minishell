/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:23:17 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/01 14:14:00 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_arg_without_quotes(int *counted, int *argc)
{
	(*counted) = 1;
	(*argc)++;
}

int	handle_quotes(char *cmd_line, int *counted, int *argc, int i)
{
	(*counted) = 1;
	(*argc)++;
	return (get_end_of_quote_pos(&cmd_line[i]));
}

int	handle_spaces(char *cmd_line, int *counted, int i)
{
	(*counted) = 0;
	return (get_whitespace(&cmd_line[i + 1]));
}

int	get_argc(char *cmd_line)
{
	int	counted;
	int	argc;
	int	i;

	argc = 0;
	counted = 0;
	i = 0;
	while (cmd_line[i] != '\0' && cmd_line[i] != '|')
	{
		if (cmd_line[i] == ' ')
			i += handle_spaces(cmd_line, &counted, i);
		else if ((cmd_line[i] == '"' || cmd_line[i] == '\'') && !counted)
			i += handle_quotes(cmd_line, &counted, &argc, i);
		else if (!counted)
		{
			handle_arg_without_quotes(&counted, &argc);
		}
		else if ((cmd_line[i] == '"' || cmd_line[i] == '\'') && counted)
		{
			if (is_char_escaped(cmd_line, i) && are_slashes_even(cmd_line, i))
				i += get_end_of_quote_pos(&cmd_line[i]);
		}
		i++;
	}
	return (argc);
}
