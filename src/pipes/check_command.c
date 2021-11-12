/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:18:27 by julian            #+#    #+#             */
/*   Updated: 2021/11/05 10:12:57 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_absolute_command(char *argv, t_var **data)
{
	int		i;
	int		cmd_len;
	char	**path;

	if (access(argv, X_OK) == -1)
	{
		(*data)->status = 127;
		return (print_error_cmd(argv));
	}
	cmd_len = ft_strlen(ft_strrchr(argv, '/')) - 1;
	path = get_path((*data)->env);
	if (path == NULL)
		return (1);
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

static int	check_cmd_helper(char **argv)
{
	if (!ft_strcmp(argv[0], "<") || !ft_strcmp(argv[0], ">") \
		|| !ft_strcmp(argv[0], "<<") || !ft_strcmp(argv[0], ">>"))
		return (1);
	if (check_builtin_command(argv[0]))
		return (1);
	return (0);
}

int	check_command(char **argv, t_var **data)
{
	int		i;
	char	*cmd;
	char	**path;

	if (check_cmd_helper(argv))
		return (1);
	path = get_path((*data)->env);
	if (path == NULL)
		return (pr_error2(argv[0], "No such file or directory"));
	i = -1;
	while (path[++i] != NULL && path != NULL)
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

static int	check_ending(char **cmd_line, t_var **data)
{
	int	i;

	i = ft_strlen(*cmd_line);
	while ((*cmd_line)[--i] == ' ' && i)
		;
	if ((*cmd_line)[i] == '<' || (*cmd_line)[i] == '>')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data)->status = 258;
		if (*cmd_line)
			return (0);
	}
	return (1);
}

int	check_relative_and_absolute(char **argv, t_var **data, char **cmd_line)
{
	int		check_cmd;
	char	*tmp;

	if (argv[0][0] == '.')
	{		
		tmp = get_command(argv[0], data);
		free(argv[0]);
		argv[0] = tmp;
	}
	if (!check_redirections(argv, data))
		return (0);
	if (!check_ending(cmd_line, data))
		return (0);
	if (!ft_strcmp(argv[0], "/") || !ft_strcmp(argv[0], ".")
		|| !ft_strcmp(argv[0], "..") || !ft_strcmp(argv[0], "$"))
		return (print_error_cmd(argv[0]));
	if (ft_strchr(argv[0], '/'))
		check_cmd = check_absolute_command(argv[0], data);
	else if (ft_strchr(argv[0], '='))
		check_cmd = 1;
	else
		check_cmd = check_command(argv, data);
	return (check_cmd);
}
