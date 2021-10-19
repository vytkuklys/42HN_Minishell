/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:18:27 by julian            #+#    #+#             */
/*   Updated: 2021/10/19 19:11:10 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_absolute_command(char *argv, t_var **data)
{
	int		i;
	int		cmd_len;
	char	**path;

	if (access(argv, X_OK) == -1)
		return (print_error_cmd(argv));
	cmd_len = ft_strlen(ft_strrchr(argv, '/')) - 1;
	path = get_path((*data)->env);
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
	(*data)->status = 127;
	return (print_error_cmd(argv));
}

int	check_command(char **argv, t_var **data)
{
	int		i;
	char	*cmd;
	char	**path;

	if (!ft_strcmp(argv[0], "<") || !ft_strcmp(argv[0], ">") \
		|| !ft_strcmp(argv[0], "<<") || !ft_strcmp(argv[0], ">>"))
		return (1);
	if (check_builtin_command(argv[0]))
		return (1);
	path = get_path((*data)->env);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin2(&path[i], argv[0]);
		if (access(cmd, X_OK) != -1)
		{
			free(cmd);
			free_array(&path);
			return (1);
		}
		free(cmd);
	}
	free_array(&path);
	(*data)->status = 127;
	return (print_error_cmd(argv[0]));
}

static int	check_ending(char **argv, t_var **data)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	if (!ft_strcmp(argv[i - 1], "<") || !ft_strcmp(argv[i - 1], ">") \
		|| !ft_strcmp(argv[i - 1], "<<") || !ft_strcmp(argv[i - 1], ">>"))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data)->status = 258;
		return (0);
	}
	return (1);
}

int	check_relative_and_absolute(char **argv, t_var **data)
{
	int	check_cmd;

	if (!check_ending(argv, data))
		return (0);
	if (ft_strchr(argv[0], '/'))
		check_cmd = check_absolute_command(argv[0], data);
	else
		check_cmd = check_command(argv, data);
	return (check_cmd);
}
