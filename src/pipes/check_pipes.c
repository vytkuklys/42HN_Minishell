/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:33:01 by julian            #+#    #+#             */
/*   Updated: 2021/11/02 14:26:59 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_ending(char *s, t_var *data)
{
	int	i;

	i = ft_strlen(s);
	while (s[--i] == ' ')
		;
	if (s[i] == '|')
	{
		if (s[i - 1] == '\\')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			data->status = 258;
			return (1);
		}
		if (s[i - 1] == '|' && s[i - 2] != '\\')
		{
			printf("minishell: OR operator not supported\n");
			data->status = 258;
			return (1);
		}
	}
	return (0);
}

static int	check_pipes_error(char *s, t_var *data)
{
	int		i;
	char	*error;

	i = 0;
	error = "minishell: syntax error near unexpected token `|";
	while (s[++i] != '\0')
	{
		if (s[i] == '|' && is_in_quotes(s, i))
		{
			i++;
			while (s[i] == ' ' && s[i] != '\0')
				i++;
			if (s[i] == '|')
			{
				if (s[i + 1] == '|')
					printf("%s|'\n", error);
				else
					printf("%s'\n", error);
				data->status = 258;
				return (1);
			}
		}
	}
	return (0);
}

static int	check_pipes_beginning(char *s, t_var *data)
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
		data->status = 258;
		return (1);
	}
	else
		return (0);
}

int	check_pipes(char **cmd_line, t_var *data)
{	
	if (check_pipes_beginning(*cmd_line, data))
		return (1);
	if (check_ending(*cmd_line, data))
		return (1);
	if (check_pipes_error(*cmd_line, data))
		return (1);
	return (0);
}
