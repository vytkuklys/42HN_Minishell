/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:43:29 by julian            #+#    #+#             */
/*   Updated: 2021/10/12 18:55:57 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static char **redirect_out(char ***argv)
{
	int		i;
	int		out;
	char	**command;
	
	i = -1;
	while (argv[0][++i] != NULL)
	{
		if (!ft_strcmp(argv[0][i], ">"))
		{
			i++;
			out = open(argv[0][i], O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (out < 0)
			{
				pr_error(strerror(errno), argv[0][i]);
				return (NULL);
			}
			if (dup2(out, STDOUT_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (NULL);
			}	
		}	
	}
	i = 0;
	while (ft_strcmp(argv[0][i], ">") && argv[0][i] != NULL)
		i++;
	command = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ft_strcmp(argv[0][i], ">") && argv[0][i] != NULL)
	{
		command[i] = ft_strdup(argv[0][i]);
		i++;
	}
	command[i] = NULL;
	return (command);
}

static char **redirect_append(char ***argv)
{
	int		i;
	int		out;
	char	**command;
	
	i = -1;
	while (argv[0][++i] != NULL)
	{
		if (!ft_strcmp(argv[0][i], ">>"))
		{
			i++;
			out = open(argv[0][i], O_CREAT | O_RDWR | O_APPEND, 0777);
			if (out < 0)
			{
				pr_error(strerror(errno), argv[0][i]);
				return (NULL);
			}
			if (dup2(out, STDOUT_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (NULL);
			}	
		}	
	}
	i = 0;
	while (ft_strcmp(argv[0][i], ">>") && argv[0][i] != NULL)
		i++;
	command = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ft_strcmp(argv[0][i], ">>") && argv[0][i] != NULL)
	{
		command[i] = ft_strdup(argv[0][i]);
		i++;
	}
	command[i] = NULL;
	return (command);	
}

static char **redirect_in(char ***argv)
{
	int		i;
	int		j;
	int		in;
	int		arr_len;
	char	**command;

	arr_len = 0;
	while (argv[0][++arr_len] != NULL)
		arr_len++;
	i = -1;
	while (argv[0][++i] != NULL)
	{
		if (!ft_strcmp(argv[0][i], "<"))
		{
			i++;
			in = open(argv[0][i], O_RDONLY);
			if (in < 0)
			{
				pr_error(strerror(errno), argv[0][i]);
				return (NULL);
			}
			if (dup2(in, STDIN_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (NULL);
			}	
		}	
	}
	i = 0;
	while (ft_strcmp(argv[0][i], "<") && argv[0][i] != NULL)
		i++;
	command = (char **)malloc(sizeof(char *) * (arr_len - i - 1));
	j = 0;
	while (argv[0][i + 2] != NULL)
	{
		command[j++] = ft_strdup(argv[0][i + 2]);
		i++;
	}
	command[j] = NULL;
	return (command);	
}

static char	**redirect_heredoc(char ***argv)
{
	int		i;
	char	*line;
	int		fd[2];
	char	**command;

	pipe(fd);
	i = -1;
	while (argv[0][++i] != NULL)
	{
		if (!ft_strcmp(argv[0][i], "<<"))
			break ;
	}
	write(1, "heredoc> ", 9);
	line = get_next_line(0);
	while (line)
	{
		line = ft_strtrim(line, "\n");
		if (ft_strcmp(line, argv[0][i + 1]) == 0)
		{
			free(line);
			break ;
		}
		write(1, "heredoc> ", 9);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = get_next_line(0);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while (ft_strcmp(argv[0][i], "<<") && argv[0][++i] != NULL)
		i++;
	command = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ft_strcmp(argv[0][i], "<<") && argv[0][i] != NULL)
	{
		command[i] = ft_strdup(argv[0][i]);
		i++;
	}
	command[i] = NULL;
	return (command);
}


static void	prepare_execution(char ***argv, char *envp[])
{
	int		i;
	int		red_out;
	int		red_in;
	int		red_append;
	int		red_heredoc;
	char	**command;
	
	i = 0;
	while (argv[0][i] != NULL)
		i++;
	if (!ft_strcmp(argv[0][i - 1], "<") || !ft_strcmp(argv[0][i - 1], ">"))
	{
		printf("minishell: parse error near `\\n'\n");
		return ;
	}
	red_out = exists_red_out(argv[0]);
	if (red_out)
	{
		command = redirect_out(argv);
		if (command == NULL)
			return ;
	}
	red_append = exists_red_append(argv[0]);
	if (red_append)
	{
		command = redirect_append(argv);
		if (command == NULL)
			return ;
	}
	red_in = exists_red_in(argv[0]);
	if (red_in)
	{
		command = redirect_in(argv);
		if (command == NULL)
			return ;
	}
	red_heredoc = exists_red_heredoc(argv[0]);
	if (red_heredoc)
	{
		command = redirect_heredoc(argv);
		if (command == NULL)
			return ;
	}
	if (command == NULL)
		command = *argv;

	execute_child(command, envp);
}

void	execute_child(char **command, char *envp[])
{
	int		i;
	char	*cmd;
	char	**path;

	if (!execute_builtin_command(command, envp))
		return ;
	path = get_path(envp);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(&path[i], command[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, command, envp);
		free(cmd);
	}
	free_array(path);
	free_array(command);
}

void	execute_single_command(char ***argv, char *envp[])
{
	int	check_cmd;
	int	id;

	check_cmd = check_command(*argv, envp);
	if (check_cmd == 0)
		return ;
	id = fork();
	if (id < 0)
		return (perror("FORK"));
	if (id == 0)
		prepare_execution(argv, envp);
	else
		wait(NULL);
}
