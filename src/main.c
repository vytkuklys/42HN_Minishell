/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/09 00:51:08 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_command(char *cmd_line)
{
    int i;

    i = 0;
    if (cmd_line == NULL)
        return NULL;
    while (cmd_line[i] != ' ' && cmd_line[i] != '\0')
        i++;
    return ft_substr(cmd_line, 0, i);
}

char	*get_pwd(char *cmd_line)
{
    char	*output;
	int		i;

	if (cmd_line == NULL) //add clean exit
		return (NULL);
	i = 0;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] != ' ')
        	return ("pwd: too many arguments");
		i++;
	}
    output = getenv("PWD");
    return (output);
}

int process_command_line(char **cmd_line, t_var **data)
{
    char *cmd;
    char *output;

	if ((*data)->env == NULL)
		return (0);
    output = NULL;
    cmd = get_command(*cmd_line);
    if (!ft_strncmp(cmd, "pwd", 3))
	{
        output = get_pwd((*cmd_line) + 3);
    	write(1, output, ft_strlen(output));
		write(1, "\n", 1);
	}
	else if (!ft_strncmp(cmd, "echo", 4))
	{
		output = get_echo(*cmd_line, data);
	}
	else if (!ft_strncmp(cmd, "env", 3))
    {
		get_env((*data)->env);
    }
    else if (!ft_strncmp(cmd, "exit", 4))
    {
        output = get_exit((*cmd_line) + 4);
        if (!output)
            return (0);
        write(1, output, ft_strlen(output));
    }
    else if (!ft_strncmp(cmd, "export", 6))
    {
        ft_export(*cmd_line, data);
    }
    else if (!ft_strncmp(cmd, "unset", 5))
    {
        ft_unset(*cmd_line, data);
    }
    // else if (ft_strchr(cmd, '='))
    // {
    //     // set_variables(*cmd_line, data);
    // }
	else if (cmd[0] != '\0')
	{
		write(1, "minishell: command not found: ", 31);
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
	}
    free(*cmd_line);
    *cmd_line = ft_calloc(1, 1);
	if (*cmd_line == NULL) //add clean exit
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
            if (!process_command_line(&cmd_line, &data))
                break ;
            print_prompt(PROMPT);
        }
        else
            cmd_line = ft_strjoin(&cmd_line, buff);
    }
    free_str(&cmd_line);
    return (0);
}
