/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:46:15 by jludt             #+#    #+#             */
/*   Updated: 2021/10/17 23:57:19 by vkuklys          ###   ########.fr       */
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

static char **handle_heredoc(char **argv)
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

static char **handle_other_red(char **argv)
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
	argv = handle_heredoc(argv);
	argv = handle_other_red(argv);
	execute_cmd(argv, data);
}
