/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 00:01:03 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/08 01:12:40 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_export_error(char *arg, int *flag, char *error)
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

void print_prompt(int prompt)
{
	if (prompt == PROMPT)
		write(1, "\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;33m➜ \033[0;37m", 49);
	else if (prompt == ERR0R_PROMPT)
		write(1, "\n\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;31m➜ \033[0;37m", 50);
}
