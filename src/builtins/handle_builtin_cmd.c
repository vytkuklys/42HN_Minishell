/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:05:23 by julian            #+#    #+#             */
/*   Updated: 2021/11/05 10:20:20 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_command(char *cmd_line, t_var **data)
{
	int		i;
	int		whitespace;
	char	*cmd;
	char	*tmp;

	if (data == NULL)
		data = NULL;
	whitespace = get_whitespace(cmd_line);
	i = whitespace;
	if (cmd_line == NULL)
		return (NULL);
	while (cmd_line[i] != ' ' && cmd_line[i] != '\0')
		i++;
	cmd = ft_substr(cmd_line, whitespace, i - whitespace);
	if (cmd[0] != '.' && ft_strchr(cmd, '/'))
	{
		tmp = ft_strdup(ft_strrchr(cmd, '/') + 1);
		free(cmd);
		cmd = tmp;
		tmp = NULL;
	}
	return (cmd);
}

int	handle_variable(char **argv, t_var **data)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (argv[i] != NULL)
	{
		if (is_arg_valid(argv[i], &flag))
		{
			if (does_export_var_exists((*data)->env, argv[i]) != -1)
			{
				if (modify_arg_in_env((*data)->env, argv[i]) == -1)
					return (-1);
			}
		}
		i++;
	}
	return (1);
}

int	execute_builtin_command(char **cmd_line, t_var **data, char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", get_len(cmd, "pwd")))
		(*data)->error = ft_pwd();
	else if (!ft_strncmp(cmd, "echo", get_len(cmd, "echo")))
		(*data)->error = get_echo(cmd_line);
	else if (!ft_strncmp(cmd, "env", get_len(cmd, "env")))
		(*data)->error = get_env((*data)->env);
	else if (!ft_strncmp(cmd, "exit", get_len(cmd, "exit")))
		(*data)->error = get_exit((*cmd_line) + 4, data, cmd_line);
	else if (!ft_strncmp(cmd, "export", get_len(cmd, "export")))
		(*data)->error = ft_export(cmd_line, data);
	else if (!ft_strncmp(cmd, "unset", get_len(cmd, "unset")))
		(*data)->error = ft_unset(cmd_line, data);
	else if (!ft_strncmp(cmd, "cd", get_len(cmd, "cd")))
		(*data)->error = ft_cd(cmd_line);
	else if (ft_strchr(cmd, '='))
		(*data)->error = handle_variable(cmd_line, data);
	if ((*data)->error)
	{
		(*data)->status = 0;
		return (0);
	}
	return (1);
}

int	check_builtin_command(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}
