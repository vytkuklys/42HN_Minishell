/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 00:01:03 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/29 00:02:29 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_prompt(int prompt)
{
	if (prompt == PROMPT)
		write(1, "\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;33m➜ \033[0;37m", 49);
	else if (prompt == ERR0R_PROMPT)
		write(1, "\n\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;31m➜ \033[0;37m", 50);
}
