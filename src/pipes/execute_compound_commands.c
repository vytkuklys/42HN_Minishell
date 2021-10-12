/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/10/12 15:21:52 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//void	execute_cmd(char *cmds, char *envp[])
void	execute_cmd(char ***argv, char *envp[], int i)
{
	int		j;
	char	*cmd;
	char	**path;

	if (!execute_builtin_command(argv[i], envp))
		return ;
	path = get_path(envp);
	j = -1;
	while (path[++j] != NULL)
	{
		cmd = ft_strjoin(&path[j], argv[i][0]);
		if (cmd == NULL)
			return ;
		execve(cmd, argv[i], envp);
		free(cmd);
	}
	free_array(path);
}

static void	child_process(char ***argv, char *envp[], int fd[][2], int i, int pipes)
{
	if (i == 0)
	{
		if (dup2(fd[i][1], STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS1"));
	}
	else if (i == pipes)
	{
		if ((dup2(fd[i - 1][0], STDIN_FILENO) < 0))
			return (perror("CHILD_PROCESS2"));
	}
	else
	{
		if ((dup2(fd[i - 1][0], STDIN_FILENO) < 0) || (dup2(fd[i][1], STDOUT_FILENO) < 0))
			return (perror("CHILD_PROCESS3"));
	}
	close_fds(pipes, fd);
	execute_cmd(argv, envp, i);
}

static void	pipe_fork(char ***argv, char *envp[], int pipes)
{
	int		fd[pipes][2];
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < pipes)
		pipe(fd[i]);
	i = -1;
	while (++i <= pipes)
	{
		pid = fork();
		if (pid < 0)
			return (perror("FORK"));
		if (pid == 0)
			child_process(argv, envp, fd, i, pipes);
	}
	i = -1;
	while (++i < pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	i = -1;
	while (++i <= pipes)
		wait(NULL);
}

void	execute_compound_commands(char ***argv, char *envp[], int pipes)
{
	int		*check_cmd;
	int		i;

	check_cmd = (int *)malloc(sizeof(int) * pipes + 1);
	i = -1;
	while (++i <= pipes)
		check_cmd[i] = check_command(&argv[i][0], envp);
	i = -1;
	while (++i <= pipes)
	{
		if (check_cmd[i] == 0)
		{
			free_argv(argv);
			return ;
		}
	}
	free(check_cmd);
	pipe_fork(argv, envp, pipes);
}
