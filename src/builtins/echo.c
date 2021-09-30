/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:02:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/30 23:30:52 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_start_of_quote(char *cmd_line)
{
    int i;

	if (cmd_line == NULL) //add clean exit / free stuff
        return (NULL);
    i = 0;
    while (!(cmd_line[i] == '\0' || cmd_line[i] == '\'' || cmd_line[i] == '\"'))
	{
		if (cmd_line[i] == '\\' && ft_strchr("'\"", cmd_line[i + 1]))
			i++;
        i++;
	}
    if (cmd_line[i] != '\0')
		return &cmd_line[i];
    return (NULL);
}

int get_end_of_quote_pos(char *str)
{
	 int i;

	if (str == NULL) //add clean exit / free stuff
        return (-1);
    i = 1;
    while (str[i] != '\0' && str[i] != str[0])
	{
		if (str[i] == '\\' && str[i + 1] == str[0])
			i++;
        i++;
	}
    if (str[i] == str[0])
		return (i);
    return (-1);
}

char *get_text_outside_quotes(char *cmd_line)
{
    char	*str;
    int		i;
    int		j;
	int		spaces;

	spaces = get_whitespace(cmd_line);
    str = ft_calloc(ft_strlen(cmd_line) - spaces + 1, 1);
    if (str == NULL) //add clean exit / free stuff
        return (NULL);
    i = spaces;
    j = 0;
    while (cmd_line[i] != '\0' && !ft_strchr("\"';|", cmd_line[i]))
		i += add_char_to_text(&str, &cmd_line[i], &j) + 1;
    return (str);
}

char *get_text_in_quotes(char *start)
{
	int	i;
	int j;
	char *quote;
	char quote_mark;

	quote_mark = start[0];
	quote = ft_calloc(ft_strlen(start), 1);
	if (quote == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (start[i] != '\0' && start[i] != quote_mark)
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
	return (quote);
}

int is_echo_flag_set(char *cmd_line)
{
	int		i;
	int		j;
	char	flag[4];

	i = 0;
	j = 0;
	while (cmd_line[i] != '\0' && j < 3)
	{
		if (cmd_line[i] == ' ' && i == 0)
			i += get_whitespace(cmd_line);
		flag[j] = cmd_line[i];
		j++;		
		i++;
	}
	flag[j] = '\0';
	if (!ft_strncmp(flag, "-n ", 3))
		return (i);
	return (0);
}

int add_text_echo(char **output, char *cmd_line)
{
	char	*start;
	int		i;
	int		len;
	char	*tmp_in;
	char	*tmp_out;

	len = ft_strlen(cmd_line);
	fprintf(stderr, "%d\n", len);
	i = 0;
	while (i <= len && i != -1)
	{
    	tmp_out = get_text_outside_quotes(&cmd_line[i]);
		*output = ft_strjoin(output, tmp_out);
		free_str(tmp_out);
		start = get_start_of_quote(&cmd_line[i]);
		if (start == NULL)
			return (1);
		tmp_in = get_text_in_quotes(start);
		if (tmp_in == NULL) //add clean exit / free stuff
			return (1);
		i = ft_strrstr(cmd_line, start) + get_end_of_quote_pos(start) + 1;
		*output = ft_strjoin(output, tmp_in);
		free_str(tmp_in);
	}
	return (0);
}

char    *get_echo(char *cmd_line)
{
	char	*output;
	int		flag;

    output = ft_calloc(1, 1);
    if (output == NULL) //add clean exit / free stuff
        return (NULL);
	flag = is_echo_flag_set(cmd_line);	
	if (!flag)
		add_text_echo(&output, &cmd_line[flag]);
	else
		add_text_echo(&output, cmd_line);
	if (!is_echo_flag_set(cmd_line))
		output = ft_strjoin(&output, "\n");
	return (output);
}
