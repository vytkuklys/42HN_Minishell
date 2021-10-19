/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 00:01:27 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/19 06:31:01 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char
	*get_text_outside_quotes(char *cmd_line, int *index, int len, char **env)
{
	int		i;
	int		j;
	char	*text;

	if (cmd_line == NULL)
		return (NULL);
	text = ft_calloc(ft_strlen(cmd_line) + 1, 1);
	if (text == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_line[i] != '\0' && i < len)
		i += add_char_to_text(&text, cmd_line, &j, i) + 1;
	(*index) += i;
	expand_variable(&text, env, '"');
	return (text);
}

char	*get_text_in_quotes(char *s, int *index, char **env)
{
	int		i;
	int		j;
	char	*quote;

	quote = ft_calloc(ft_strlen(s), 1);
	if (quote == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\')
			i += add_slashes(&quote, &s[i], &j) - 1;
		else if (s[i] == s[0] && is_char_escaped(s, i) && are_slashes_even(s, i))
			break ;
		else if (!(s[i] == s[0] && !is_char_escaped(s, i)))
		{
			quote[j] = s[i];
			j++;
		}
		i++;
	}
	expand_variable(&quote, env, s[0]);
	(*index) += i + 1;
	return (quote);
}

char	*get_arg(char *cmd_line, int len, char **env)
{
	int		i;
	char	*arg;
	char	*tmp;

	arg = ft_calloc(1, 1);
	if (arg == NULL)
		return (NULL);
	i = 0;
	while (cmd_line && cmd_line[i] != '\0' && i < len)
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
			tmp = get_text_in_quotes(cmd_line, &i, env);
		else
			tmp = get_text_outside_quotes(cmd_line, &i, len, env);
		arg = ft_strjoin(&arg, tmp);
		free(tmp);
		tmp = NULL;
		if (arg == NULL)
			return (NULL);
	}
	return (arg);
}

int	get_argv(char *cmd_line, char **argv, char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	// while (cmd_line[i] != '\0' && cmd_line[i] != '|' && cmd_line[i] != ';')
	while (cmd_line[i] != '\0' && cmd_line[i] != '|')
	{
		len = 0;
		if (cmd_line[i] != ' ')
		{
			len = get_arg_len(&cmd_line[i]);
			argv[j] = get_arg(&cmd_line[i], len, env);
			if (argv[j] == NULL)
				return (-1);
			j++;
			i += len;
		}
		else
			i++;
	}
	argv[j] = NULL;
	return (0);
}
