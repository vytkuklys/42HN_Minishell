/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:02:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/29 02:34:56 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_index_of_first_quote(char *cmd_line)
{
    int i;

    if (cmd_line == NULL) //add clean exit
        return (NULL);
    i = 0;
    while (cmd_line[i] != '\0' && cmd_line[i] != '\'' && cmd_line[i] != '\"')
        i++;
    if (cmd_line[i] != '\0')
        return (i);
    return (-1);
}

int get_whitespace_count(char *cmd_line)
{
	int space;

	while (*cmd_line && ft_strchr(" \t\v\f\r\b", *cmd_line))
		space++;
	return (space);
}

/*slash is jumped over and*/
char *get_echo_beginning(char *cmd_line)
{
    char *str;
    int i;
    int j;

    str = ft_calloc(ft_strlen(cmd_line), 1);
    if (str == NULL) //add clean exit
        return (NULL);
    i = 0;
    j = 0;
    while (cmd_line[i] != '\0' && !ft_strchr("\"';|", cmd_line[i]))
    {
        if (cmd_line[i] == '\\')
        {
            i++;
			if (cmd_line[i] != '\0')
			{
				str[j] = cmd_line[i];
				j++;
			}
        }
		i++;
    }
}

char    *get_echo(char *cmd_line, char *cmd)
{
	char	*output;
	int		quote;
	int		i;

    // output = ft_calloc(1, 1);
    if (output == NULL) //add clean exit
        return (NULL);
	i = 0;
	quote = get_index_of_first_quote(cmd_line[i]);
    if (quote > 0 && cmd_line[quote - 1] == '\\')
        output = get_echo_beginning(cmd_line);
	return (output);
}
