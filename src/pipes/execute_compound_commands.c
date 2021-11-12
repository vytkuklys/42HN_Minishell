/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/11/05 10:49:24 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_fd(int **fd, int i, int pipes, int heredocs)
{
	if (i == 0)
	{
		dup2(fd[i][1], STDOUT_FILENO);
	}
	else if (i == pipes)
	{
		if (heredocs == 0)
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
		}
	}
	else
	{
		if (heredocs == 0)
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			dup2(fd[i][1], STDOUT_FILENO);
		}
		else
			dup2(fd[i][1], STDOUT_FILENO);
	}
}

static void	child(char ***argv, t_var **data, int **fd, int i)
{
	int	heredocs;

	signal(SIGINT, process_signal);
	signal(SIGQUIT, SIG_DFL);
	heredocs = count_heredocs(argv[i]);
	handle_heredoc(argv, i);
	redirect_fd(fd, i, (*data)->pipes, heredocs);
	close_fds((*data)->pipes, fd);
	free_fds((*data)->pipes, fd);
	if (handle_redirections(argv, i) == -1)
	{
		(*data)->status = 1;
		exit (1);
	}
	execute_cmd(argv[i], data);
}

static void	pipe_fork(char ***argv, t_var **data)
{
	int		**fd;
	pid_t	pid;
	int		i;

	fd = init_fds((*data)->pipes);
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
		if (count_heredocs(argv[i]))
			wait(NULL);
	}
	close_fds((*data)->pipes, fd);
	free_fds((*data)->pipes, fd);
	i = -1;
	while (++i <= (*data)->pipes)
		wait(NULL);
}

void	execute_compound_commands(char ***argv, t_var **data, char **cmd_line)
{
	int		*check_cmd;
	int		i;

	check_cmd = (int *)malloc(sizeof(int) * (*data)->pipes + 1);
	if (check_cmd == NULL)
		exit(1);
	i = -1;
	while (++i <= (*data)->pipes)
		check_cmd[i] = check_relative_and_absolute(&argv[i][0], data, cmd_line);
	free(check_cmd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipe_fork(argv, data);
	signal(SIGINT, process_signal);
}
