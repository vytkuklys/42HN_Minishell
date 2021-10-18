/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:50:04 by jludt             #+#    #+#             */
/*   Updated: 2021/10/15 18:53:16 by julian           ###   ########.fr       */
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

char	**redirect_heredoc(char **argv, int pos, int nbr_heredocs)
{
	int		i;
	char	*line;
	int		fd[2];

	pipe(fd);
	i = -1;
	while (argv[++i] != NULL)
		if (!ft_strcmp(argv[i], "<<"))
			break ;
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, argv[i + 1]) == 0)
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
	return (update_argv(argv, "<<"));
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
