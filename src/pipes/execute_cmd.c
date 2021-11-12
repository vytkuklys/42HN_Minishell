/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:31:48 by julian            #+#    #+#             */
/*   Updated: 2021/11/05 10:16:25 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_cmd(char **argv, t_var **data)
{
	char	*cmd;
	int		result;

	cmd = get_command(*argv, data);
	result = execute_builtin_command(argv, data, cmd);
	free(cmd);
	if (!result)
		return (1);
	return (0);
}

static void	exit_process(char ***argv, t_var **data)
{
	if ((*data)->pipes > 0)
		exit(1);
	write(1, "minishell: ", 12);
	write(1, argv[0][0], ft_strlen(argv[0][0]));
	write(1, ": command not found\n", 21);
	free_array(argv);
	exit(1);
}

void	execute_cmd(char **argv, t_var **data)
{
	int		i;
	char	*cmd;
	char	**path;

	if (is_builtin_cmd(argv, data))
	{
		free_array(&argv);
		exit(EXIT_SUCCESS);
	}
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
	(*data)->status = 1;
	free_array(&path);
	exit_process(&argv, data);
}
