/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:23:17 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/08 00:30:33 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_argc(char *cmd_line)
{
	int	argc;
	int counted;
	int	i;
	int quote;

	if (!are_quotes_valid(cmd_line) || !are_slashes_valid(cmd_line))
		return (-1);
	argc = 0;
	counted = 0;
	quote = 0;
	i = 0;
	while (cmd_line[i] != '\0' && cmd_line[i] != '|' && cmd_line[i] != ';')
	{
		if (cmd_line[i] == ' ')
		{
			counted = 0;
			i += get_whitespace(&cmd_line[i + 1]);
		}
		else if (ft_strchr("'\"", cmd_line[i]) && !counted)
		{
			i += get_end_of_quote_pos(&cmd_line[i]);
			counted = 1;
			argc++;
		}
		else if (!counted)
		{
			counted = 1;
			argc++;
		}
		else if (ft_strchr("'\"", cmd_line[i]) && counted)
		{
			if (is_char_escaped(cmd_line, i) && are_slashes_even(cmd_line, i))
				i += get_end_of_quote_pos(&cmd_line[i]);
		}
		i++;
	}
	return (argc);
}

// int main(void)
// {
// 	get_argc("\\\"");
// 	return 0;
// }