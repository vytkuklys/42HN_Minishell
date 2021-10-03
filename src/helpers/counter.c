/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:50:32 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/03 01:40:07 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_end_of_quote_pos(char *str)
{
	int i;
	if (str == NULL) //add clean exit / free stuff
        return (-1);
    i = 1;
    while (str[i] != '\0' && str[i] != str[0])
        i++;
    if (str[i] == str[0])
		return (i);
    return (-1);
}

int get_end_of_str_pos(char *str)
{
	int i;

	if (str == NULL) //add clean exit / free stuff
		return (-1);
	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	return (i);
}

int	get_whitespace(char *cmd_line)
{
	int	space;

    space = 0;
	while (*cmd_line && ft_strchr(" \t\v\f\r\b", *cmd_line))
	{
		space++;
		cmd_line++;
	}
	return (space);
}
