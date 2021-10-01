/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:50:18 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/01 01:24:16 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int add_char_to_text(char **str, char *cmd_line, int *j)
{
	int i;

	i = 0;
	if (cmd_line && cmd_line[i] == '\\')
	{
		i++;
		if (cmd_line[i] != '\0')
		{
			(*str)[*j] = cmd_line[i];
			(*j)++;
		}
	}
	else if (cmd_line && cmd_line[i] == ' ')
	{
		(*str)[*j] = cmd_line[i];
		i += get_whitespace(cmd_line + i + 1);
		(*j)++;
	}
	else if (cmd_line && cmd_line[i])
	{
		(*str)[*j] = cmd_line[i];
		(*j)++;
	}
	return (i);
}

int add_slashes(char **quote, char *start, int *j)
{
	int	i;

	if (start == NULL || *quote == NULL) //add clean exit / free stuff
		return (-1);
	i = 0;
	printf("%lu!", strlen(start));
	while (start && start[i] == '\\')
	{
		if (i % 2 == 0)
		{
			(*quote)[(*j)] = '\\';
			(*j)++;
		}
		i++;
	}
	return (i * 2);
}
// int get_end_of_quote_pos(char *str)
// {
// 	int i;
// 	if (str == NULL) //add clean exit / free stuff
//         return (-1);
//     i = 1;
// 	fprintf(stderr, "%s-", str);
//     while (str[i] != '\0' && str[i] != str[0])
// 	{
// 		// if (str[i] == '\\' && str[i + 1] == str[0])
// 		// 	i++;
//         i++;
// 	}
// 	printf("%c\n", str[i]);
//     if (str[i] == str[0])
// 		return (i);
//     return (-1);
// }

// int main(void)
// {
// 	char *quote = calloc(10, 1);
	
// 	int j = 0;
// 	printf("%d", get_end_of_quote_pos("\"\\\\\""));
// 	// printf("\n%d - %s", j, quote);
// 	return (0);
// }