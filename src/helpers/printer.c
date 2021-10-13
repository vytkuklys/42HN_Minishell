/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 00:01:03 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/13 03:52:31 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_cmd_not_found(char *cmd)
{
    int i;
    int quote;

    i = 0;
    quote = 0;
    while (cmd && cmd[i] != '\0')
    {
        if ((cmd[i] == '"' || cmd[i] == '\''))
            quote++;
        i++;
    }
    if (i == quote)
        write(1, "minishell: command not found: \n", 32);
    else
        printf("minishell: command not found: %s\n", cmd);
    return (0);
}

int	print_export_error(char *arg, int *flag, char *error)
{
	int	i;

	if (arg == NULL || error == NULL)
		return (0);
	i = 0;
	if (*flag == 0)
	{
		write(1, error, ft_strlen(error));
		while (arg[i] != '\0' && arg[i] != '=')
		{
			write(1, &arg[i], 1);
			i++;
		}
		write(1, "\n", 2);
		(*flag)++;
	}
	return (0);
}

void	print_prompt(int prompt)
{
	char	*p;
	char	*pe;

	p = "\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;33m➜ \033[0;37m";
	pe = "\n\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;31m➜ \033[0;37m";
	if (prompt == PROMPT)
		write(1, p, ft_strlen(p));
	else if (prompt == ERR0R_PROMPT)
		write(1, pe, ft_strlen(pe));
}
