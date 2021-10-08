/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/10/08 16:01:37 by julian           ###   ########.fr       */
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

static void	child_process(char **cmds, char *envp[], int fd[][2], int i, t_operators *op)
{
	if (i == 0)
	{
		if (dup2(fd[i][1], STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS1"));
	}
	else if (i == op->pipes)
	{
		if ((dup2(fd[i - 1][0], STDIN_FILENO) < 0))
			return (perror("CHILD_PROCESS2"));
	}
	else
	{
		if ((dup2(fd[i - 1][0], STDIN_FILENO) < 0)|| (dup2(fd[i][1], STDOUT_FILENO) < 0))
			return (perror("CHILD_PROCESS3"));
	}
	close_fds(op->pipes, fd);
	execute_cmd(cmds[i], envp);
}

static void	pipe_fork(char **cmds, char *envp[], t_operators *op)
{
	int		fd[op->pipes][2];
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < op->pipes)
		pipe(fd[i]);
	i = -1;
	while (++i < (op->pipes + 1))
	{
		pid = fork();
		if (pid < 0)
			return (perror("FORK"));
		if (pid == 0)
			child_process(cmds, envp, fd, i, op);
	}
	i = -1;
	while (++i < op->pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	i = -1;
	while (++i < (op->pipes + 1))
		wait(NULL);
}

static void	exec_multiple_pipes(char *cmd_line, char *envp[], t_operators *op)
{
	char	**cmds;
	int		*check_cmd;
	int		i;
	
	fprintf(stderr, "cmd_line0 = %s\n", cmd_line);
	cmds = ft_split_pipe(cmd_line, '|', " ");
	i = -1;
	while (cmds[++i] != NULL)
		fprintf(stderr, "cmds[%d] = %s\n", i, cmds[i]);
	check_cmd = (int *)malloc(sizeof(int) * op->pipes + 1);
	i = -1;
	while (++i < op->pipes + 1)
		check_cmd[i] = check_single_command(cmds[i], envp);
	i = -1;
	while (++i < op->pipes + 1)
		if (check_cmd[i] == 0)
			return ;
	free(check_cmd);
	pipe_fork(cmds, envp, op);
}

void	execute_compound_commands(t_operators *op, char *cmd_line, char *envp[])
{
	if (op->heredoc == 0 && op->last_pipe == 0  && op->cmdor == 0 \
		&& op->append == 0 && op->redirect_int == 0 && op->redirect_out == 0)
			exec_multiple_pipes(cmd_line, envp, op);
	// if (op->heredoc == 0 && op->last_pipe == 1  && op->cmdor == 0 \
	// 	&& op->append == 0 && op->redirect_int == 0 && op->redirect_out == 0)
	// 		exec_multiple_pipes2(cmd_line, envp, op);
	initialize_operators(op);
}