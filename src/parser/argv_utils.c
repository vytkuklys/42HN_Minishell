/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:58:36 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/02 16:30:03 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exp_arg_len(char *cmd_line, char **env, int len)
{
	char	*expanded;
	int		exp_len;

	expanded = ft_strdup(cmd_line);
	expand_variable(&expanded, env, cmd_line[0], cmd_line);
	exp_len = get_arg_len(expanded);
	free(expanded);
	expanded = NULL;
	if (len != exp_len)
		return (exp_len + 2);
	return (len);
}

int	get_arg_len(char *cmd_line)
{
	int	i;
	int	len;
	int	str_len;

	i = 0;
	len = 0;
	str_len = ft_strlen(cmd_line);
	while (cmd_line[len] != '\0' && cmd_line[len] != ' ' && str_len > len)
	{
		if (cmd_line[len] == '"' || cmd_line[len] == '\'')
			len += get_end_of_quote_pos(&cmd_line[len]) + 1;
		else
			len += get_end_of_arg_pos(&cmd_line[len]);
		i += len;
	}
	return (len);
}

int	add_char_to_text(char **str, char *src, int *j, int i)
{
	int	whitespace;

	whitespace = 0;
	if (src && src[i] == '\\')
		return (add_slashes(str, &src[i], j, get_slash_type(src, i)) - 1);
	if (src && src[i] == ' ')
	{
		(*str)[*j] = src[i];
		whitespace += get_whitespace(src + i + 1);
		(*j)++;
	}	
	else if (src && src[i])
	{
		if (src[i] != '"' && src[i] != '\'')
		{
			(*str)[*j] = src[i];
			(*j)++;
		}
		else if (is_char_escaped(src, i) && !are_slashes_even(src, i))
		{
			(*str)[*j] = src[i];
			(*j)++;
		}
	}
	return (whitespace);
}

int	add_slashes(char **quote, char *start, int *j, char quote_mark)
{
	int		i;
	int		slashes;

	if (start == NULL || *quote == NULL)
		return (-1);
	slashes = 0;
	i = 0;
	while (start && start[i] == '\\')
	{
		i++;
	}
	if (quote_mark == '"' && i % 2)
		slashes = i / 2 + 1;
	else if (quote_mark == '"')
		slashes = i / 2;
	else
		slashes = i;
	while (slashes > 0)
	{
		(*quote)[(*j)] = '\\';
		(*j)++;
		slashes--;
	}
	return (i);
}
