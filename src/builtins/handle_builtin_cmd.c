/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:05:23 by julian            #+#    #+#             */
/*   Updated: 2021/10/20 11:06:37 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_command(char *cmd_line, t_var **data)
{
	int		i;
	int		whitespace;
	char	*cmd;

	whitespace = get_whitespace(cmd_line);
	i = whitespace;
	if (cmd_line == NULL)
		return (NULL);
	while (cmd_line[i] != ' ' && cmd_line[i] != '\0')
		i++;
	cmd = ft_substr(cmd_line, whitespace, i - whitespace);
	if (ft_strchr(cmd, '/') && check_absolute_command(cmd, data))
		cmd = ft_strrchr(cmd, '/') + 1;
	return (cmd);
}

int	handle_cmd_terminator(char **cmd_line, t_var **data)
{
	int		last_char;
	char	*new;

	new = NULL;
	last_char = get_last_char_index(*cmd_line);
	if (last_char != -1 && (*data)->error != -1 \
		&& (*cmd_line)[last_char] == ';')
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

// int get_terminator_index(char **cmd_line)
// {
//     int len;

//     if (cmd_line == NULL)
//         return (-1);
//     len = 0;
//     while (cmd_line[len] != NULL)
//     {
//         if (ft_strlen(cmd_line[len]) == 1 && cmd_line[len][0] == ';')
//             return (len);
//         len++;
//     }
//     return (-1);
// }

// char **get_cmd_copy(char **cmd_line, int len)
// {
//     char	**copy;
//     int		l;
// 	int		i;

// 	l = ft_strlen_2d(cmd_line);
// 	i = 0;
//     copy = ft_calloc(l + 1, sizeof(char *));
//     while (cmd_line[i] != NULL && i < len)
// 	{
// 		copy[i] = ft_strdup(cmd_line[i]);
// 		i++;
// 	}
// 	if (len == -1)
// 	{
// 		while (cmd_line[i] != NULL)
// 		{
// 			copy[i] = ft_strdup(cmd_line[i]);
// 			i++;
// 		}
// 	}
// 	copy[i] = NULL;
//     return (copy);
// }

int	execute_builtin_command(char **cmd_line, t_var **data, char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", get_len(cmd, "pwd")))
		(*data)->error = ft_pwd();
	else if (!ft_strncmp(cmd, "echo", get_len(cmd, "echo")))
		(*data)->error = get_echo(cmd_line, data);
	else if (!ft_strncmp(cmd, "env", get_len(cmd, "env")))
		(*data)->error = get_env((*data)->env);
	else if (!ft_strncmp(cmd, "exit", get_len(cmd, "exit")))
		(*data)->error = get_exit((*cmd_line) + 4, data);
	else if (!ft_strncmp(cmd, "export", get_len(cmd, "export")))
		(*data)->error = ft_export(cmd_line, data);
	else if (!ft_strncmp(cmd, "unset", get_len(cmd, "unset")))
		(*data)->error = ft_unset(cmd_line, data);
	else if (!ft_strncmp(cmd, "cd", get_len(cmd, "cd")))
		(*data)->error = ft_cd(cmd_line);
	if (handle_cmd_terminator(cmd_line, data) == -1)
	{
		(*data)->status = 3;
		return (0);
	}
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
// int	check_builtin_command(char *cmd)
// {
// 	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd))
// 		|| !ft_strncmp(cmd, "cd", ft_strlen(cmd))
// 		|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd))
// 		|| !ft_strncmp(cmd, "export", ft_strlen(cmd))
// 		|| !ft_strncmp(cmd, "unset", ft_strlen(cmd))
// 		|| !ft_strncmp(cmd, "env", ft_strlen(cmd))
// 		|| !ft_strncmp(cmd, "exit", ft_strlen(cmd)))
// 		return (1);
// 	else
// 		return (0);
// }
