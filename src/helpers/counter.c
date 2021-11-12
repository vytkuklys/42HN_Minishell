/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:50:32 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/02 16:33:39 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_len(char *s1, char *s2)
{
	int	len_1;
	int	len_2;

	if (s1 == NULL && s2 != NULL)
		return (ft_strlen(s2));
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	if (len_1 > len_2)
		return (len_1);
	return (len_2);
}

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
	return (i);
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

char	*trim_back(char *arg, int len)
{
	char	*new;

	if (arg[0] == '$')
		new = ft_substr(arg, 0, len);
	else
		new = ft_substr(arg, 0, len - 2);
	free(arg);
	arg = NULL;
	return (new);
}
