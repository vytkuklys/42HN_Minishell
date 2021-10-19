/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:54:58 by jludt             #+#    #+#             */
/*   Updated: 2021/10/18 15:30:15 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_command(char **argv, char *envp[])
{
	int		i;
	char	*cmd;
	char	**path;

	if (!ft_strcmp(argv[0], "<") || !ft_strcmp(argv[0], ">") \
		|| !ft_strcmp(argv[0], "<<") || !ft_strcmp(argv[0], ">>"))
		return (1);
	if (check_builtin_command(argv[0]))
		return (1);
	path = get_path(envp);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin2(&path[i], argv[0]);
		if (cmd == NULL)
			break ;
		if (access(cmd, X_OK) != -1)
		{
			free(cmd);
			free_array(&path);
			return (1);
		}
		free(cmd);
	}
	free_array(&path);
	return (print_error_cmd(argv[0]));
}

int	check_absolute_command(char *argv, char *envp[])
{
	int		i;
	int		cmd_len;
	char	**path;

	if (access(argv, X_OK) == -1)
		return (print_error_cmd(argv));
	cmd_len = ft_strlen(ft_strrchr(argv, '/')) - 1;
	path = get_path(envp);
	i = -1;
	while (path[++i] != NULL)
	{
		if (!ft_strncmp(path[i], argv, ft_strlen(argv - cmd_len)))
		{
			free_array(&path);
			return (1);
		}
	}
	free_array(&path);
	return (print_error_cmd(argv));
}

void	close_fds(int pipes, int fd[][2])
{
	int	i;

	i = -1;
	while (++i < pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

int count_pipes(char *cmd_line)
{
	char	quote;
	int		i;
	int		pipes;

	quote = '\0';
	i = 0;
	pipes = 0;
	while (cmd_line[i] != '\0')
	{
		if (!quote && cmd_line[i] == '|' && !is_char_escaped(cmd_line, i))
			pipes++;
		if (!quote && (cmd_line[i] == '\'' || cmd_line[i] == '"'))
			quote = cmd_line[i];
		else if (quote && cmd_line[i] == quote && !is_char_escaped(cmd_line, i))
			quote = '\0';
		i++;
	}
	return (pipes);
}
