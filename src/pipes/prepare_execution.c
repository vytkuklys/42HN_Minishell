/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:46:15 by jludt             #+#    #+#             */
/*   Updated: 2021/10/13 14:54:52 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prepare_execution(char **argv, char *envp[])
{
	int		i;
	int		red_out;
	int		red_in;
	int		red_append;
	int		red_heredoc;
	char	**command;
	
	command = NULL;
	i = 0;
	while (argv[i] != NULL)
		i++;
	if (!ft_strcmp(argv[i - 1], "<") || !ft_strcmp(argv[i - 1], ">") \
		|| !ft_strcmp(argv[i - 1], "<<") || !ft_strcmp(argv[i - 1], ">>"))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	red_out = exists_red_out(argv);
	if (red_out)
	{
		command = redirect_out(argv);
		if (command == NULL)
			return ;
	}
	red_append = exists_red_append(argv);
	if (red_append)
	{
		command = redirect_append(argv);
		if (command == NULL)
			return ;
	}
	red_in = exists_red_in(argv);
	if (red_in)
	{
		if (red_out || red_append)
			command = redirect_in(command);
		else
			command = redirect_in(argv);
		if (command == NULL)
			return ;
	}
	red_heredoc = exists_red_heredoc(argv);
	if (red_heredoc)
	{
		command = redirect_heredoc(argv);
		if (command == NULL)
			return ;
	}
	if (command == NULL)
		command = argv;
	execute_cmd(command, envp);
}
