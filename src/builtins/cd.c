/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 05:00:26 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/03 15:05:24 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **cmd_line)
{
	int		ch;

	if (cmd_line == NULL)
		return (-1);
	if (ft_strlen_2d(cmd_line) != 2)
	{
		ch = chdir(getenv("HOME"));
		if (ch < 0)
			perror("cd");
		return (1);
	}
	if (!ft_strcmp(cmd_line[1], "~"))
		ch = chdir(getenv("HOME"));
	else
		ch = chdir(cmd_line[1]);
	if (ch < 0)
		perror("cd");
	return (1);
}
