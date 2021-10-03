/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:18:45 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/03 00:10:11 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_exit(char *cmd_line)
{
	int	argc;

	if (exists_pipes(cmd_line))
		return ("exit: too many arguments\n");
	argc = get_argc(cmd_line);
	if (argc == -1)
		return ("minishell: invalid arguments\n");
	if (argc > 1)
		return ("exit: too many arguments\n");
	return (NULL);
}
