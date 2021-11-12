/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:43:29 by julian            #+#    #+#             */
/*   Updated: 2021/11/05 10:56:08 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_error(t_var **data)
{
	if ((*data)->error == -1)
	{
		write(1, "minishell: Memory allocation error\n", 36);
		(*data)->status = 2;
		(*data)->error = 0;
		return (-1);
	}
	else if ((*data)->error == -2)
		(*data)->exit = 1;
	(*data)->error = 0;
	return (0);
}

void	process_quit_signal(int signum)
{
	signum = 1;
	kill(getpid(), SIGINT);
}

int	execute_cmd_in_child(char **argv, t_var **data)
{
	int		id;

	id = fork();
	if (id < 0)
	{
		perror("FORK");
		return (-1);
	}
	if (id == 0)
	{
		changetermios(1);
		signal(SIGINT, process_signal);
		signal(SIGQUIT, process_quit_signal);
		execute_cmd(argv, data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&(*data)->status);
		init_signals();
	}
	return (0);
}

int	execute_single_command(char ***argv, t_var **data, char **cmd_line)
{
	char	*cmd;
	int		i[2];

	if (get_whitespace(*cmd_line) == ft_strlen(*cmd_line))
		return (0);
	ft_memset(i, 0, 8);
	while (argv[0][0][i[0]] != '\0')
		if (argv[0][0][i[0]++] == ' ')
			i[1] = 1;
	if (i[1] == 0)
		if (!check_relative_and_absolute(argv[0], data, cmd_line))
			return (0);
	cmd = get_command((*argv)[0], data);
	handle_heredoc(argv, 0);
	if (handle_redirections(argv, 0) == -1)
	{
		(*data)->status = 1;
		free(cmd);
		return (-1);
	}
	execute_builtin_command(argv[0], data, cmd);
	free(cmd);
	if ((*data)->error)
		return (handle_error(data));
	return (execute_cmd_in_child(argv[0], data));
}
