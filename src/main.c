/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/11 06:20:37 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_command(char *cmd_line)
{
    int i;
    int whitespace;

    whitespace = get_whitespace(cmd_line);
    i = whitespace;
    if (cmd_line == NULL)
        return NULL;
    while (cmd_line[i] != ' ' && cmd_line[i] != '\0')
        i++;
    return ft_substr(cmd_line, whitespace, i);
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
        process_command_line(&new,
            data, get_command(new));
    }
    return (0);
}

int process_command_line(char **cmd_line, t_var **data, char *cmd)
{
    if (!ft_strncmp(cmd, "pwd", 3))
        ft_pwd();
	else if (!ft_strncmp(cmd, "echo", 4))
		(*data)->error = get_echo(*cmd_line, data);
	else if (!ft_strncmp(cmd, "env", 3))
		get_env((*data)->env);
    else if (!ft_strncmp(cmd, "exit", 4))
        (*data)->error = get_exit((*cmd_line) + 4);
    else if (!ft_strncmp(cmd, "export", 6))
        (*data)->error = ft_export(*cmd_line, data);
    else if (!ft_strncmp(cmd, "unset", 5))
        (*data)->error = ft_unset(*cmd_line, data);
    else if (!ft_strncmp(cmd, "cd", 2))
        ft_cd(*cmd_line, data);
	else if (cmd[0] != '\0')
		printf("minishell: command not found: %s\n", cmd);
    if (handle_cmd_terminator(cmd_line, data) == -1)
        return (0);
    free(*cmd_line);
    *cmd_line = ft_calloc(1, 1);
	if (*cmd_line == NULL || (*data)->error == -1)
		return (0);
    return (1);
}

void process_signal(int signum)
{
	if (signum == SIGINT)
    {
    	write(2, "\b\b", 2);
		print_prompt(ERR0R_PROMPT);
    }
}

int main(int argc, char **argv, char **env)
{
    int bytes;
    char buff[2];
    char *cmd_line;
    t_var   *data;

    data = (t_var *)malloc(sizeof(t_var));
	if (!data)
		return (-1);
    bytes = 1;
	if (argc == 0 && argv == NULL)
		argc = 0;
    signal(SIGINT, process_signal);
    signal(SIGQUIT, process_signal);
	print_prompt(PROMPT);
	cmd_line = ft_calloc(1, 1);
    init_data(env, &data);
    while (bytes > 0)
    {
        bytes = read(1, &buff, 1);
        buff[bytes] = '\0';
        if (buff[0] == '\n')
        {
            if (!process_command_line(&cmd_line, &data, get_command(cmd_line)))
                break ;
            print_prompt(PROMPT);
        }
        else
            cmd_line = ft_strjoin(&cmd_line, buff);
    }
    free_2d_array(&data->env);
    free_str(&cmd_line);
    return (0);
}
