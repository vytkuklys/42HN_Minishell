/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 00:01:03 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/07 19:08:36 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_prompt(int prompt, int i)
{
	if (prompt == PROMPT && i == -1)
		write(1, "\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;33m➜ \033[0;37m", 49);
	else if (prompt == ERR0R_PROMPT && i == -1)
		write(1, "\n\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;31m➜ \033[0;37m", 50);
	else if (prompt == 2)
	{
		while (i--)
			write(1, "pipe ", 5);
		write(1, "pipe> ", 6);
	}
}
