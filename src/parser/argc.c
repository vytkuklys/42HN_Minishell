/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:23:17 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/13 09:35:21 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_argc(char *cmd_line)
{
	int	argc;
	int counted;
	int	i;

	if (!are_quotes_valid(cmd_line) || !are_slashes_valid(cmd_line))
		return (-1);
	argc = 0;
	counted = 0;
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
		i++;
	}
	return (argc);
}

// int main(int argc, char **argv)
// {
//     printf("%d", get_argc("\\\" 123 123 123\"123\" ''''2 \"123123\""));
//     if (argv == NULL)
//         return (1);
//     return (0);
// }