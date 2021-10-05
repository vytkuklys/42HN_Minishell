/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_compound_commands_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:26:45 by julian            #+#    #+#             */
/*   Updated: 2021/10/05 19:38:50 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	initialize_operators(t_operators *op)
{
	op->pipes = 0;
	op->heredoc = 0;
	op->append = 0;
	op->redirect_int = 0;
	op->redirect_out = 0;
}
