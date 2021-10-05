/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:33:01 by julian            #+#    #+#             */
/*   Updated: 2021/10/05 15:33:16 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	scan_cmd_line(t_operators *operators, char *cmd_line)
{
	int	i;
	
	if (cmd_line[0] == '|')
	{
		printf("minishell: parse error near `|'\n");
		return (1);
	}
	i = -1;
	while (cmd_line[++i] != '\0')
	{
		if (cmd_line[i] == '|' && cmd_line[i + 1] != '|')
			operators->pipes += 1;
		if (cmd_line[i] == '|' && cmd_line[i + 1] != ' ' \
			&& cmd_line[i + 1] == '|')
			{
				printf("minishell: parse error near `|'\n");
				return (1);
			}
	}
	return (0);
}