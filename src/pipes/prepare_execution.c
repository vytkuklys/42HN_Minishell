/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:46:15 by jludt             #+#    #+#             */
/*   Updated: 2021/10/18 15:34:11 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_handling(char **argv)
{
	int	i;
	
	i = 0;
	while (argv[i] != NULL)
		i++;
	if (!ft_strcmp(argv[i - 1], "<") || !ft_strcmp(argv[i - 1], ">") \
		|| !ft_strcmp(argv[i - 1], "<<") || !ft_strcmp(argv[i - 1], ">>"))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

char **handle_heredoc(char **argv)
{
	int nbr_heredocs;
	int	i;
	int	j;
	
	nbr_heredocs = count_heredocs(argv);
	i = -1;
	j = 0;
	while (argv[++i] != NULL)
	{
		if (!ft_strcmp(argv[i], "<<"))
		{
			argv = redirect_heredoc(argv, ++j, nbr_heredocs);
			i = -1;
			continue ;
		}
	}
	return (argv);
}

static char **handle_redirections(char **argv)
{
	int i;

	i = -1;
	while (argv[++i] != NULL)
	{		
		if (!ft_strcmp(argv[i], ">"))
		{
			argv = redirect_out(argv);
			i = -1;
			continue ;
		}	
		if (!ft_strcmp(argv[i], ">>"))
		{
			argv = redirect_append(argv);
			i = -1;
			continue ;
		}
		if (!ft_strcmp(argv[i], "<"))
		{
			argv = redirect_in(argv);
			i = -1;
			continue ;
		}
	}
	return (argv);
}

void	prepare_execution(char **argv, t_var **data)
{
	if (error_handling(argv))
		return ;
	argv = handle_redirections(argv);
	execute_cmd(argv, data);
}
