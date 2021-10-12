/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:54:58 by jludt             #+#    #+#             */
/*   Updated: 2021/10/12 18:12:12 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_command(char **argv, char *envp[])
{
	int		i;
	char	*cmd;
	char	**path;

	if (!ft_strcmp(argv[0], "<") || !ft_strcmp(argv[0], ">"))
		return (1);
	if (check_builtin_command(argv[0]))
		return (1);
	path = get_path(envp);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(&path[i], argv[0]);
		if (cmd == NULL)
			break ;
		if (access(cmd, X_OK) != -1)
		{
			free(cmd);
			free_array(path);
			return (1);
		}
		free(cmd);
	}
	free_array(path);
	return (print_error_cmd(argv[0]));
}

int	execute_builtin_command(char **argv, char *env[])
{
	char	*cmd;
	char	*cmd_line;
	char	*output;

	cmd_line = ft_strjoin_space(argv);
	cmd = get_command(cmd_line);
	if (!ft_strcmp(cmd, "pwd"))
	{
		ft_pwd();
		free(cmd_line);
		return (0);
	}
	else if (!ft_strcmp(cmd, "echo"))
	{
		output = get_echo(cmd_line, env);
		//write(1, output, ft_strlen(output));
		return (0);
	}
	else if (!ft_strcmp(cmd, "env"))
	{
		get_env(env);
		free(cmd_line);
		return (0);
	}
	else if (!ft_strcmp(cmd, "exit"))
	{
		output = get_exit((cmd_line) + 4);
		if (!output)
			return (0);
		write(1, output, ft_strlen(output));
		free(cmd_line);
		return (0);
	}
	return (1);
}

void	initialize_operators(t_op *op)
{
	op->pipes = 0;
	op->heredoc = 0;
	op->append = 0;
	op->redirect_int = 0;
	op->redirect_out = 0;
}

int	exists_red_out(char **s)
{
	int	i;
	int	red_out;

	red_out = 0;
	i = -1;
	while (s[++i] != NULL)
	{
		if (!ft_strcmp(s[i], ">"))
			red_out++;
	}
	return(red_out);
}

int	exists_red_append(char **s)
{
	int	i;
	int	red_app;

	red_app = 0;
	i = -1;
	while (s[++i] != NULL)
	{
		if (!ft_strcmp(s[i], ">>"))
			red_app++;
	}
	return(red_app);
}

int	exists_red_in(char **s)
{
	int	i;
	int	red_in;

	red_in = 0;
	i = -1;
	while (s[++i] != NULL)
	{
		if (!ft_strcmp(s[i], "<"))
			red_in++;
	}
	return(red_in);
}

int	exists_red_heredoc(char **s)
{
	int	i;
	int	red_in;

	red_in = 0;
	i = -1;
	while (s[++i] != NULL)
	{
		if (!ft_strcmp(s[i], "<<"))
			red_in++;
	}
	return(red_in);
}

void	close_fds(int pipes, int fd[][2])
{
	int	i;

	i = -1;
	while (++i < pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	get_redirections(t_op *op, char *s)
{
	op->pipes = exists_pipes(s);
	// op->heredoc = 0;
	// op->append = 0;
	// op->redirect_int = 0;
	op->redirect_out = exists_red_out(&s);
	
}