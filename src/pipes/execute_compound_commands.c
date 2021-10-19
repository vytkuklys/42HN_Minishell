/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/10/19 12:41:12 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_fd(int fd[][2], int i, int pipes, int heredocs)
{
	if (i == 0)
	{
		if (dup2(fd[i][1], STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS1"));
	}
	else if (i == pipes)
	{
		if (heredocs == 0)
			if ((dup2(fd[i - 1][0], STDIN_FILENO) < 0))
				return (perror("CHILD_PROCESS2"));
	}
	else
	{
		if (heredocs == 0)
		{
			if ((dup2(fd[i - 1][0], 0) < 0) || (dup2(fd[i][1], 1) < 0))
				return (perror("CHILD_PROCESS3"));
		}
		else
		{
			if (dup2(fd[i][1], 1) < 0)
				return (perror("CHILD_PROCESS4"));
		}
	}
}

static void	child(char ***argv, t_var **data, int fd[][2], int i)
{
	int	heredocs;

	// signal(SIGINT, SIG_IGN);
	heredocs = count_heredocs(argv[i]);
	argv[i] = handle_heredoc(argv[i]);
	redirect_fd(fd, i, (*data)->pipes, heredocs);
	close_fds((*data)->pipes, fd);
	prepare_execution(argv[i], data);
}

static void	pipe_fork(char ***argv, t_var **data)
{
	int		fd[(*data)->pipes][2];
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < (*data)->pipes)
		pipe(fd[i]);
	i = -1;
	while (++i <= (*data)->pipes)
	{
		pid = fork();
		if (pid < 0)
			return (perror("FORK"));
		if (pid == 0)
			child(argv, data, fd, i);
		if (i < (*data)->pipes && count_heredocs(argv[i]))
			waitpid(pid, NULL, 0);
	}
	i = -1;
	while (++i < (*data)->pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	i = -1;
	while (++i <= (*data)->pipes)
		wait(NULL);
}

int	check_relative_and_absolute(char **argv, char *envp[])
{
	int	check_cmd;

	if (ft_strchr(argv[0], '/'))
		check_cmd = check_absolute_command(argv[0], envp);
	else
		check_cmd = check_command(argv, envp);
	return (check_cmd);
}

void	execute_compound_commands(char ***argv, t_var **data)
{
	int		*check_cmd;
	int		i;
	
	check_cmd = (int *)malloc(sizeof(int) * (*data)->pipes + 1);
	i = -1;
	while (++i <= (*data)->pipes)
		check_cmd[i] = check_relative_and_absolute(&argv[i][0], (*data)->env);
	i = -1;
	while (++i <= (*data)->pipes)
	{
		if (check_cmd[i] == 0)
		{
			free(check_cmd);
			return ;
		}
	}
	free(check_cmd);
	pipe_fork(argv, data);
}
