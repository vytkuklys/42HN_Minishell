/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:43:29 by julian            #+#    #+#             */
/*   Updated: 2021/10/05 16:16:41 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_single_child(char *cmd0, char *envp[])
{
	int		i;
	char	*cmd;
	char	**path;
	char	**cmd1;
	
	path = get_path(envp);
	cmd1 = ft_split(cmd0, ' ');
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(&path[i], cmd1[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, cmd1, envp);
		free(cmd);
	}
	exit_failure(path, cmd1);
}

void	execute_single_command(char *cmd, char *envp[])
{
	int	check_cmd;
	int	id;

	check_cmd = check_single_command(cmd, envp);
	if (check_cmd == 0)
		return ;
	id = fork();
	if (id < 0)
		return (perror("FORK"));
	if (id == 0)
		execute_single_child(cmd, envp);
	else
		wait(NULL);
}
