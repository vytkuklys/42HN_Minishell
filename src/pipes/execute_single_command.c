/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:43:29 by julian            #+#    #+#             */
/*   Updated: 2021/10/19 19:12:15 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_error(t_var **data)
{
	if ((*data)->error == -1)
	{
		write(1, "minishell: Memory allocation error\n", 36);
		(*data)->status = 2;
		return (-1);
	}
	else if ((*data)->error == -2)
		(*data)->exit = 1;
	(*data)->error = 0;
	return (0);
}

int	execute_single_command(char ***argv, t_var **data)
{
	int	id;

	if (!check_relative_and_absolute(argv[0], data))
		return (0);
	execute_builtin_command(argv[0], data, get_command((*argv)[0], data));
	if ((*data)->error)
		return (handle_error(data));
	id = fork();
	if (id < 0)
	{
		perror("FORK");
		return (-1);
	}
	if (id == 0)
	{
		argv[0] = handle_heredoc(argv[0]);
		prepare_execution(argv[0], data);
	}
	else
		wait(NULL);
	return (0);
}
