/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/15 03:17:49 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
		free(src[i++]);
	free(src);
	i = 0;
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
			free_array(path);
			return (1);
		}
	}
	free_array(path);
	return (print_error_cmd(argv));
}

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
        process_command_line(&new, data, get_command(new, data));
    }
    return (0);
}

int process_command_line(char **cmd_line, t_var **data, char *cmd)
{
    if (!ft_strncmp(cmd, "pwd", get_len(cmd, "pwd")))
        ft_pwd();
	else if (!ft_strncmp(cmd, "echo", get_len(cmd, "echo")))
		(*data)->error = get_echo(*cmd_line, data);
	else if (!ft_strncmp(cmd, "env", get_len(cmd, "env")))
		get_env((*data)->env);
    else if (!ft_strncmp(cmd, "exit", get_len(cmd, "exit")))
        (*data)->error = get_exit((*cmd_line) + 4);
    else if (!ft_strncmp(cmd, "export", get_len(cmd, "export")))
        (*data)->error = ft_export(*cmd_line, data);
    else if (!ft_strncmp(cmd, "unset", get_len(cmd, "unset")))
        (*data)->error = ft_unset(*cmd_line, data);
    else if (!ft_strncmp(cmd, "cd", get_len(cmd, "cd")))
        ft_cd(*cmd_line, data);
    else if (!ft_strncmp(cmd, "history", get_len(cmd, "history")))
        print_history((*data)->history);
	else if (cmd[0] != '\0')
        print_cmd_not_found(cmd);
    if (handle_cmd_terminator(cmd_line, data) == -1)
        return (0);
	if ((*data)->error == -1)
		return (0);
    return (1);
}

void process_signal(int signum)
{
	if (signum == SIGINT)
    {
        rl_on_new_line();
	    rl_replace_line("", 0);
	    rl_redisplay();
		print_error_prompts();
    }
}

int main(int argc, char **argv, char **env)
{
    char *cmd_line;
    t_var   *data;

    data = (t_var *)malloc(sizeof(t_var));
	if (!data)
		return (-1);
	if (argc == 0 && argv == NULL && env == NULL)
		argc = 0;
    signal(SIGINT, process_signal);
    signal(SIGQUIT, process_signal);
    init_data(env, &data);
    while (1)
	{
		cmd_line = readline(print_prompts());
        if (!cmd_line)
            break ;
		if (cmd_line && *cmd_line)
        {
            add_history(cmd_line);
            if (!process_command_line(&cmd_line, &data, get_command(cmd_line, &data)))
                break ;
        }
		free(cmd_line);
	}
    free_data(&data, &cmd_line);
    exit(0);
}
