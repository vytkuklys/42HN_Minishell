/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 00:01:27 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/07 12:22:02 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_text_outside_quotes(char *cmd_line, int *index, int len)
{
    int		i;
    int		j;
    char	*text;

	if (cmd_line == NULL)
		return (NULL);
    text = ft_calloc(ft_strlen(cmd_line) + 1, 1);
    if (text == NULL) //add clean exit / free stuff
        return (NULL);
	i = 0;
    j = 0;
    while (cmd_line[i] != '\0' && !ft_strchr("\"';|", cmd_line[i]) && i < len)
		i += add_char_to_text(&text, &cmd_line[i], &j) + 1;
	(*index) += i;
    return (text);
}

char *get_text_in_quotes(char *start, int *index)
{
	int	i;
	int j;
	char *quote;

	quote = ft_calloc(ft_strlen(start), 1);
	if (quote == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (start[i] != '\0' && start[i] != start[0])
	{
		if (start[i] == '\\')
		{
			i += add_slashes(&quote, &start[i], &j);
			continue ;
		}
		quote[j] = start[i];
		j++;
		i++;
	}
	(*index) += i + 1;
	return (quote);
}

char *get_arg(char *cmd_line, int len)
{
	int		i;
	char	*arg;
	char	*tmp;

	arg = ft_calloc(1, 1);
	if (arg == NULL)
		return (NULL);
	i = 0;
	if (!len)
		return NULL;
	while (cmd_line && cmd_line[i] != '\0' && i < len)
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
			tmp = get_text_in_quotes(cmd_line, &i);
		else
			tmp = get_text_outside_quotes(cmd_line, &i, len);
		arg = ft_strjoin(&arg, tmp);
		free(tmp);
		tmp = NULL;
	}
	i = 0;
	return (arg);
}

int get_argv(char *cmd_line, char **argv)
{
	int	i;
	int	j;
	int len;

	i = 0;
	j = 0;
	while (cmd_line[i] != '\0' && cmd_line[i] != '|' && cmd_line[i] != ';')
	{
		len = 0;
		if (cmd_line[i] != ' ')
		{
			len = get_arg_len(&cmd_line[i]);
			argv[j] = get_arg(&cmd_line[i], len);
			j++;
			i += len;
		}
		else
			i++;
	}
	argv[j] = NULL;
	return (0);
}
