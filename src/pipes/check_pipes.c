/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:33:01 by julian            #+#    #+#             */
/*   Updated: 2021/10/12 10:41:55 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_last(char *s)
{
	int	i;
	int	chmod;

	chmod = 0;
	i = ft_strlen(s);
	if (s[--i] == '|')	
	{
		if (s[--i] != '\\')
		{
			printf("minishell: parse error near `|'\n");
			return (1);
		}
	}
	return (0);
}

static int	check_parse_error(char *s)
{
	int	i;

	i = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == '|' && s[i + 1] == ' ' && s[i + 2] == '|' \
			&& s[i - 1] != '\\')
		{
			if (s[i + 3])
			{
				if (s[i + 3] == '|')
				{
					printf("minishell: parse error near `||'\n");
					return (1);
				}
			}
			printf("minishell: parse error near `|'\n");
			return (1);
		}
	}
	return (0);
}

static int	check_parse_error_beginning(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '|')
	{
		if (s[i + 1] == '|')
			printf("minishell: parse error near `||'\n");
		else
			printf("minishell: parse error near `|'\n");
		return (1);
	}
	else
		return (0);
}

int	check_pipes(char **cmd_line)
{	
	if (check_parse_error_beginning(*cmd_line))
		return (1);
	if (check_parse_error(*cmd_line))
		return (1);
	if (check_last(*cmd_line))
		return (1);
	return (0);
}
