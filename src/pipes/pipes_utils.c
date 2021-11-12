/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:54:58 by jludt             #+#    #+#             */
/*   Updated: 2021/11/04 15:37:12 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(char *cmd_line)
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
		if (!quote && cmd_line[i] == '|' && !is_char_escaped(cmd_line, i)
			&& cmd_line[i + 1] == '\0')
			return (-1);
		i++;
	}
	return (pipes);
}

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

int	pr_error2(char *s1, char *s2)
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
	return (0);
}

int	print_error_cmd(char *src)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(src, 2);
	write(2, ": command not found \n", 22);
	return (0);
}

char	**get_path(char *envp[])
{
	int		i;
	char	**path;
	int		found;

	i = -1;
	found = 0;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			found = 1;
			break ;
		}
	}
	if (found == 0)
		return (NULL);
	path = ft_split(envp[i], ':');
	path[0] = ft_strtrim_free(path[0], "PATH=");
	i = -1;
	while (path[++i] != NULL)
		path[i] = ft_strjoin(&path[i], "/");
	return (path);
}
