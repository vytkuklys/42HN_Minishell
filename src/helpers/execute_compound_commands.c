/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/10/06 17:00:39 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin_command(char *cmd0, char *env[])
{
	char	*cmd;
	char	*output;
	
	cmd = get_command(cmd0);
	if (!ft_strcmp(cmd, "pwd"))
	{
		ft_pwd();
		free(cmd0);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(cmd, "echo"))
	{
		output = get_echo(cmd0, env);
		// write(1, output, ft_strlen(output));
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(cmd, "env"))
	{
		get_env(env);
		free(cmd0);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(cmd, "exit"))
	{
		output = get_exit((cmd0) + 4);
		if (!output)
			return (0);
		write(1, output, ft_strlen(output));
		free(cmd0);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

void	execute_cmd(char *cmds, char *envp[])
{
	char	*cmd;
	char	**path;
	char	**cmd1;
	int		i;

	i = execute_builtin_command(cmds, envp);
	if (i == 0)
		return ;
	path = get_path(envp);
	cmd1 = ft_split(cmds, ' ');
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(&path[i], cmd1[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, cmd1, envp);
		free(cmd);
	}
	exit_failure(path, cmd1);
}

static void	child_process(char **cmds, char *envp[], int fd[][2], int i, int pipes)
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
		if ((dup2(fd[i - 1][0], STDIN_FILENO) < 0)|| (dup2(fd[i][1], STDOUT_FILENO) < 0))
			return (perror("CHILD_PROCESS3"));
	}
	close_fds(pipes, fd);
	execute_cmd(cmds[i], envp);
}

static void	pipe_fork(char **cmds, char *envp[], int pipes)
{
	int		fd[pipes][2];
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < pipes)
		pipe(fd[i]);
	i = -1;
	while (++i < (pipes + 1))
	{
		pid = fork();
		if (pid < 0)
			return (perror("FORK"));
		if (pid == 0)
			child_process(cmds, envp, fd, i, pipes);
	}
	i = -1;
	while (++i < pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	i = -1;
	while (++i < (pipes + 1))
		wait(NULL);
}

static void	exec_multiple_pipes(char *cmd_line, char *envp[])
{
	char	**cmds;
	int		*check_cmd;
	int		pipes;
	int		i;
	
	pipes = 0;
	i = -1;
	while (cmd_line[++i] != '\0')
		if (cmd_line[i] == '|')
			pipes++;
	cmds = ft_split_trim(cmd_line, '|', " ");
	check_cmd = (int *)malloc(sizeof(int) * pipes + 1);
	i = -1;
	while (++i < pipes + 1)
		check_cmd[i] = check_single_command(cmds[i], envp);
	i = -1;
	while (++i < pipes + 1)
		if (check_cmd[i] == 0)
			return ;
	free(check_cmd);
	pipe_fork(cmds, envp, pipes);
}

void	execute_compound_commands(t_operators *op, char *cmd_line, char *envp[])
{
	if (op->heredoc == 0 && op->append == 0 && op->redirect_int == 0 \
		&& op->redirect_out == 0)
			exec_multiple_pipes(cmd_line, envp);
	initialize_operators(op);
}