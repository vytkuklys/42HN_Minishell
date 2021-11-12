/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:50:04 by jludt             #+#    #+#             */
/*   Updated: 2021/11/01 16:48:47 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_fd(int pos, int nbr_heredocs, int *fd)
{
	if (pos == nbr_heredocs)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	heredoc_signal(int signum)
{
	int	pid;

	if (signum == SIGINT)
	{	
		pid = getpid();
		write(1, "\n", 1);
		signal(SIGINT, SIG_DFL);
		set_signal_status(1);
		kill(pid, SIGINT);
	}
}

void	redirect_heredoc(char ***argv, int pos, int nbr_heredocs, int p2)
{
	int		i;
	char	*line;
	int		fd[2];

	pipe(fd);
	i = -1;
	while (argv[p2][++i] != NULL)
		if (!ft_strcmp(argv[p2][i], "<<"))
			break ;
	signal(SIGINT, heredoc_signal);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, argv[p2][i + 1]) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	handle_fd(pos, nbr_heredocs, fd);
	update_argv(argv, "<<", p2);
}

void	handle_heredoc(char ***argv, int pos)
{
	int	nbr_heredocs;
	int	i;
	int	j;

	nbr_heredocs = count_heredocs(argv[pos]);
	i = -1;
	j = 0;
	while (argv[pos][++i] != NULL)
	{
		if (!ft_strcmp(argv[pos][i], "<<"))
		{
			redirect_heredoc(argv, ++j, nbr_heredocs, pos);
			i = -1;
			continue ;
		}
	}
}

int	count_heredocs(char **argv)
{
	int	heredocs;
	int	i;

	heredocs = 0;
	i = -1;
	while (argv[++i] != NULL)
	{
		if (!ft_strcmp(argv[i], "<<"))
			heredocs++;
	}
	return (heredocs);
}
