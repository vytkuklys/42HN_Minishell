/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:05:23 by julian            #+#    #+#             */
/*   Updated: 2021/10/17 23:34:37 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_command(char *cmd_line, t_var **data)
{
    int     i;
    int     whitespace;
    char    *cmd;

    whitespace = get_whitespace(cmd_line);
    i = whitespace;
    if (cmd_line == NULL)
        return NULL;
    while (cmd_line[i] != ' ' && cmd_line[i] != '\0')
        i++;
    cmd = ft_substr(cmd_line, whitespace, i - whitespace);
    if (ft_strchr(cmd, '/') && check_absolute_command(cmd, (*data)->env))
        cmd = ft_strrchr(cmd, '/') + 1;
    return (cmd);
}

int    handle_cmd_terminator(char **cmd_line, t_var **data)
{
    int last_char;
    char    *new;

    new = NULL;
    last_char = get_last_char_index(*cmd_line);
    if (last_char != -1 && (*data)->error != -1 && (*cmd_line)[last_char] == ';')
    {
        new = ft_strdup(*cmd_line + last_char + 1);
        if (new == NULL)
            return (-1);
        free(*cmd_line);
        *cmd_line = NULL;
        execute_builtin_command(&new, data, get_command(new, data));
    }
    return (0);
}

int execute_builtin_command(char **cmd_line, t_var **data, char *cmd)
{
    if (!ft_strncmp(cmd, "pwd", get_len(cmd, "pwd")))
        (*data)->error = ft_pwd();
	else if (!ft_strncmp(cmd, "echo", get_len(cmd, "echo")))
		(*data)->error = get_echo(cmd_line, data);
	else if (!ft_strncmp(cmd, "env", get_len(cmd, "env")))
		(*data)->error = get_env((*data)->env);
    else if (!ft_strncmp(cmd, "exit", get_len(cmd, "exit")))
        (*data)->error = get_exit((*cmd_line) + 4);
    else if (!ft_strncmp(cmd, "export", get_len(cmd, "export")))
        (*data)->error = ft_export(cmd_line, data);
    else if (!ft_strncmp(cmd, "unset", get_len(cmd, "unset")))
        (*data)->error = ft_unset(cmd_line, data);
    else if (!ft_strncmp(cmd, "cd", get_len(cmd, "cd")))
        (*data)->error = ft_cd(cmd_line);
    if (handle_cmd_terminator(cmd_line, data) == -1)
        return (0);
	if ((*data)->error)
		return (0);
    return (1);
}


int	check_builtin_command(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "cd", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "export", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "unset", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "env", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (1);
	else
		return (0);
}
