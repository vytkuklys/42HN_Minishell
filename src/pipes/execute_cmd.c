/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:31:48 by julian            #+#    #+#             */
/*   Updated: 2021/10/18 00:01:02 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_cmd(char **argv, t_var **data)
{
	int		i;
	char	*cmd;
	char	**path;

	if (!execute_builtin_command(argv, data, get_command(*argv, data)))
		return ;
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, (*data)->env);
	path = get_path((*data)->env);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(&path[i], argv[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, argv, (*data)->env);
		free(cmd);
	}
	free_array(&path);
	free_array(&argv); //leak
}