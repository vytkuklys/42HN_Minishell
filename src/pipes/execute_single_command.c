/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:43:29 by julian            #+#    #+#             */
/*   Updated: 2021/10/13 15:30:37 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_cmd(char **command, char *envp[])
{
	int		i;
	char	*cmd;
	char	**path;

	if (!execute_builtin_command(command, envp))
		return ;
	path = get_path(envp);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(&path[i], command[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, command, envp);
		free(cmd);
	}
	free_array(path);
	free_array(command);
}

void	execute_single_command(char ***argv, char *envp[])
{
	int	check_cmd;
	int	id;

	check_cmd = check_command(*argv, envp);
	if (check_cmd == 0)
		return ;
	id = fork();
	if (id < 0)
		return (perror("FORK"));
	if (id == 0)
		prepare_execution(argv[0], envp);
	else
		wait(NULL);
}
