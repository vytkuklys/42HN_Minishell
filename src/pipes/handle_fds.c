/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:33:01 by julian            #+#    #+#             */
/*   Updated: 2021/10/29 15:54:09 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(int pipes, int **fd)
{
	int	i;

	i = -1;
	while (++i < pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

int	**init_fds(int pipes)
{
	int	i;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * pipes);
	if (fd == NULL)
		return (0);
	i = -1;
	while (++i < pipes)
	{
		fd[i] = (int *)malloc(sizeof(int ) * 2);
		if (fd[i] == NULL)
			return (0);
	}
	return (fd);
}

void	free_fds(int pipes, int **fd)
{
	int	i;

	i = -1;
	while (++i < pipes)
		free(fd[i]);
	free (fd);
}
