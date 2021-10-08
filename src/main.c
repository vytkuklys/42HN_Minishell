/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:39:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/08 17:21:21 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_command(char *cmd_line)
{
	int	i;

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

int	process_command_line(char **cmd_line, char **env)
{
	char		*cmd;
	char		*output;
	t_operators	op;

	if (*env == NULL)
		return (0);
	output = NULL;
	initialize_operators(&op);
	op.pipes = exists_pipes(*cmd_line);
	if (op.pipes == 0) // single command
	{
		*cmd_line = ft_strtrim(*cmd_line, " ");
		cmd = get_command(*cmd_line);
		if (!ft_strcmp(cmd, "pwd"))
		{
			output = get_pwd((*cmd_line) + 3);
			write(1, output, ft_strlen(output));
			write(1, "\n", 1);
		}
		else if (!ft_strcmp(cmd, "echo"))
			output = get_echo(*cmd_line, env);
		else if (!ft_strcmp(cmd, "env"))
		{
			get_env(env);
		}
		else if (!ft_strcmp(cmd, "exit"))
		{
			output = get_exit((*cmd_line) + 4);
			if (!output)
				return (0);
			write(1, output, ft_strlen(output));
		}
		else if (cmd[0] != '\0')
			execute_single_command(*cmd_line, env);
		free(*cmd_line);
		*cmd_line = ft_calloc(1, 1);
		if (*cmd_line == NULL) //add clean exit
			return (0);
		return (1);
	}
	else if (op.pipes > 0)
	{
		execute_compound_commands(&op, *cmd_line, env);
		free(*cmd_line);
		*cmd_line = ft_calloc(1, 1);
		if (*cmd_line == NULL) //add clean exit
			return (0);
		return (1);
	}
	else
		return (1); // compound commants -> ToDo
}

void	process_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\b\b  ", 4);
		print_prompt(ERR0R_PROMPT, -1);
	}
}

char	*get_cmd_line(int *bytes)
{
	char	buff[2];
	char	*cmd_line;

	cmd_line = ft_calloc(1, 1);
	while (*bytes > 0)
	{
		(*bytes) = read(1, &buff, 1);
		buff[*bytes] = '\0';
		if (buff[0] == '\n')
			break ;
		else
			cmd_line = ft_strjoin(&cmd_line, buff);
	}
	return (ft_strtrim(cmd_line, " "));
}

int main(int argc, char **argv, char **env)
{
	char	*cmd_line;
	char	*tmp;
	int		error;
	int		i;
	int		bytes;

	if (argc == 0 && argv == NULL)
		argc = 0;
	signal(SIGINT, process_signal);
	signal(SIGQUIT, process_signal);
	print_prompt(PROMPT, -1);
	i = 0;
	bytes = 1;
	while (bytes > 0)
	{
		error = 0;
		i = 0;
		cmd_line = get_cmd_line(&bytes);
		while (cmd_line[ft_strlen(cmd_line) - 1] == '|')
		{
			if (check_pipes(&cmd_line))
			{
				error = 1;
				break ;
			}
			if (cmd_line[ft_strlen(cmd_line) - 2] == '\\')
				break;
			print_prompt(2, i++);
			tmp = get_cmd_line(&bytes);
			if (check_pipes(&tmp))
			{
				error = 1;
				break ;
			}
			if (!check_single_command(tmp, env))
			{
				free(tmp);
				error = 1;
				break ;
			}
			cmd_line = ft_strjoin(&cmd_line, tmp);
		}
		if (error == 0)
			if (!process_command_line(&cmd_line, env))
				break ;
		if (bytes > 0)
			print_prompt(PROMPT, -1);
	}
	free_str(&cmd_line);
	return (0);
}

    // ---cd (should work when program is being executed ~ )
    // chdir("..");

    //--ctrl_c intercept
    // -- redirection > 
    // int fd = open("text.txt", O_WRONLY | O_CREAT, 0777);
    // dup2(fd, STDOUT_FILENO);
    // close(fd);
    // printf("Experimentation::Notation::Ideation");

    //-- redirection >>
    // int fd = open("text.txt", O_WRONLY | O_APPEND | O_CREAT, 0777);
    
    //-- check if file is accesible
    // int a = access("text.txt", F_OK);

    //-- check the dir that program is started from
    // char cwd[100];
    // getcwd(cwd, sizeof(cwd));
    // printf("%s", cwd);

    // while(1)
    //     pause();

    //test

// int main(int argc, char **argv, char **env)
// {
//     if (argc == 0 || argv == NULL || env == NULL)
//         return 1;
    
//     execve("/bin/echo", argv, env);
//     // write(1, "1", 1);
//     return (0);
// }
