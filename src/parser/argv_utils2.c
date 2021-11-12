/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:10:21 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/01 14:12:44 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	handle_return(char type)
{
	if (type == '\'')
		return (type);
	return ('"');
}

char	get_slash_type(char *cmd_line, int index)
{
	int		i;
	char	type;

	i = 0;
	type = '\0';
	while (cmd_line && cmd_line[i] != '\0' && i < index)
	{
		if (cmd_line[i] == '"' || cmd_line[i] == '\'')
		{
			if (is_char_escaped(cmd_line, i) && !are_slashes_even(cmd_line, i))
			{
				i++;
				continue ;
			}
			else
			{	
				if (cmd_line[i] == type)
					type = '\0';
				else
					type = cmd_line[i];
			}
		}
		i++;
	}
	return (handle_return(type));
}
