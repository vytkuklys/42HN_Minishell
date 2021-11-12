/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:46:15 by jludt             #+#    #+#             */
/*   Updated: 2021/11/01 11:35:43 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**handle_redirections(char **argv)
{
	int	i;

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
	argv = handle_redirections(argv);
	execute_cmd(argv, data);
}
