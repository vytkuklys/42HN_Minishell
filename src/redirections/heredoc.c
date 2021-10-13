/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:50:04 by jludt             #+#    #+#             */
/*   Updated: 2021/10/13 16:52:01 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**redirect_heredoc(char **argv)
{
	int		i;
	char	*line;
	int		fd[2];
	char	**command;

	pipe(fd);
	i = -1;
	while (argv[++i] != NULL)
	{
		if (!ft_strcmp(argv[i], "<<"))
			break ;
	}
	//fprintf(stderr, "test\n");
	line = readline("> ");
	while (line)
	{
		//line = ft_strtrim(line, "\n");
		if (ft_strcmp(line, argv[i + 1]) == 0)
		{
			free(line);
			break ;
		}
		//write(1, "> ", 9);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while (ft_strcmp(argv[i], "<<") && argv[++i] != NULL)
		i++;
	command = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ft_strcmp(argv[i], "<<") && argv[i] != NULL)
	{
		command[i] = ft_strdup(argv[i]);
		i++;
	}
	command[i] = NULL;
	return (command);
}
