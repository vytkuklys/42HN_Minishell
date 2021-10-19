/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:33:01 by julian            #+#    #+#             */
/*   Updated: 2021/10/15 18:56:11 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_ending(char *s)
{
	int	i;

	i = ft_strlen(s);
	if (s[--i] == '|')	
	{
		if (s[--i] == '\\')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	return (0);
}

static int	check_pipes_error(char *s)
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
					printf("minishell: syntax error \
						near unexpected token `||'\n");
					return (1);
				}
			}
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	return (0);
}

static int	check_pipes_beginning(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '|')
	{
		if (s[i + 1] == '|')
			printf("minishell: syntax error near unexpected token `||'\n");
		else
			printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else
		return (0);
}

int	check_pipes(char **cmd_line)
{	
	if (check_pipes_beginning(*cmd_line))
		return (1);
	if (check_pipes_error(*cmd_line))
		return (1);
	if (check_ending(*cmd_line))
		return (1);
	return (0);
}
