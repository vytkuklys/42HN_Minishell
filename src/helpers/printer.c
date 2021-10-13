/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 00:01:03 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/13 11:51:13 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*print_prompt(void)
{
	char *p;

	p = "\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;33m➜ \033[0;37m";
	return (p);
}

void	print_error_prompt(void)
{
	char	*pe;

	pe = "\n\U0001f476 \033[0;32m\033[1mminishell\033[0m \033[0;31m➜ \033[0;37m";
	write(1, pe, ft_strlen(pe));
}
