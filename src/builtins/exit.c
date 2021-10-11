/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:18:45 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/11 05:23:27 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exit(char *cmd_line)
{
	int	argc;

	if (exists_pipes(cmd_line))
		return (write(1, "exit: too many arguments\n", 26));
	argc = get_argc(cmd_line);
	if (argc == -1)
		return (write(1, "minishell: invalid arguments\n", 30));
	if (argc > 1)
		return (write(1, "exit: too many arguments\n", 26));
	return (-1);
}
