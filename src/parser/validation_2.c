/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 05:46:15 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/19 19:06:31 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_last_char_index(char *cmd_line)
{
	int	counted;
	int	argc;
	int	i;

	if (!are_quotes_valid(cmd_line) || !are_slashes_valid(cmd_line))
		return (-1);
	argc = 0;
	counted = 0;
	i = 0;
	while (cmd_line[i] != '\0' && cmd_line[i] != '|' && cmd_line[i] != ';')
	{
		if (cmd_line[i] == ' ')
			i += handle_spaces(cmd_line, &counted, i);
		else if (ft_strchr("'\"", cmd_line[i]) && !counted)
			i += handle_quotes(cmd_line, &counted, &argc, i);
		else if (!counted)
			handle_arg_without_quotes(&counted, &argc);
		else if (ft_strchr("'\"", cmd_line[i]) && counted)
		{
			if (is_char_escaped(cmd_line, i) && are_slashes_even(cmd_line, i))
				i += get_end_of_quote_pos(&cmd_line[i]);
		}
		i++;
	}
	return (i);
}
