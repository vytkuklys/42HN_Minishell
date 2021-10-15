/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:59:36 by julian            #+#    #+#             */
/*   Updated: 2021/10/15 01:00:34 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pr_error(char *s1, char *s2)
{
	if (s1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s2)
		ft_putstr_fd(s2, 2);
	write(2, "\n", 1);
}

void	free_array(char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
		free(src[i++]);
	free(src);
	i = 0;
}

void	exit_failure(char **path, char **cmd_n)
{
	free_array(path);
	free_array(cmd_n);
}

int	check_builtin_command(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") \
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") \
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

int	print_error_cmd(char *src)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(src, 2);
	write(2, "\n", 1);
	return (0);
}

char	**get_path(char *envp[])
{
	int		i;
	char	**path;

	i = -1;
	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	path = ft_split(envp[i], ':');
	path[0] = ft_strtrim(path[0], "PATH=");
	i = -1;
	while (path[++i] != NULL)
		path[i] = ft_strjoin(&path[i], "/");
	return (path);
}
