/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:07:37 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/04 12:36:57 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_in_quotes_norm(char *cmd_line, int *total, int i, char *quote)
{
	if (!(*quote) && (cmd_line[i] == '\'' || cmd_line[i] == '"')
		&& (!is_char_escaped(cmd_line, i) || are_slashes_even(cmd_line, i)))
	{
		(*total)++;
		(*quote) = cmd_line[i];
	}
	else if ((*quote) && cmd_line[i] == (*quote)
		&& (!is_char_escaped(cmd_line, i) || are_slashes_even(cmd_line, i)))
		(*quote) = '\0';
	else if ((*quote) && cmd_line[i] == (*quote)
		&& is_char_escaped(cmd_line, i))
		if (are_slashes_even(cmd_line, i))
			(*quote) = '\0';
}

int	is_in_quotes(char *cmd_line, int index)
{
	int		i;
	char	quote;
	int		total;

	i = 0;
	total = 0;
	quote = '\0';
	while (cmd_line[i] != '\0' && i < index)
	{
		is_in_quotes_norm(cmd_line, &total, i, &quote);
		i++;
	}
	if (total == 0 || quote == '\0')
		return (1);
	return (0);
}

int	get_redirection_count(char *cmd_line)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '>' || cmd_line[i] == '<')
		{
			r++;
			while (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (r);
}

int	*get_redirections_hash(char *cmd_line, int count)
{
	int	*hash;
	int	i;
	int	j;

	i = 0;
	j = 0;
	hash = (int *)malloc((count + 1) * sizeof(int));
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '>' || cmd_line[i] == '<')
		{
			if (is_in_quotes(cmd_line, i))
				hash[j] = get_redirection_type(cmd_line, i);
			else
				hash[j] = 0;
			while (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i++;
			j++;
		}
		i++;
	}
	hash[j] = -1;
	return (hash);
}

int	update_argv_args(char ***argv, char *cmd_line, t_var **data)
{
	int		*hash;
	int		count;

	if (argv == NULL)
		argv = NULL;
	count = get_redirection_count(cmd_line);
	if (count == 0)
		return (0);
	hash = get_redirections_hash(cmd_line, count);
	modify_argv(argv, hash, data);
	free(hash);
	return (0);
}
