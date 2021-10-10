/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:50:32 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/10 00:57:09 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_end_of_quote_pos(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == str[0] && is_char_escaped(str, i))
		{
			if (are_slashes_even(str, i))
				break ;
		}
		else if (str[i] == str[0])
			break ;
		i++;
	}
	if (str[i] == str[0])
		return (i);
	return (-1);
}

int	get_end_of_arg_pos(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		if (ft_strchr("'\"", str[i]) && is_char_escaped(str, i))
		{
			if (are_slashes_even(str, i))
				break ;
		}
		else if (ft_strchr("'\"", str[i]) && !is_char_escaped(str, i))
			break ;
		i++;
	}
	if (str[i] == '"' || str[i] == '\'')
		i += get_end_of_quote_pos(&str[i]) + 1;
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
