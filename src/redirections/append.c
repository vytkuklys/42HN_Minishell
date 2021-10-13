/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:49:31 by jludt             #+#    #+#             */
/*   Updated: 2021/10/13 14:49:33 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**redirect_append(char **argv)
{
	int		i;
	int		out;
	char	**command;
	
	i = -1;
	while (argv[++i] != NULL)
	{
		if (!ft_strcmp(argv[i], ">>"))
		{
			i++;
			out = open(argv[i], O_CREAT | O_RDWR | O_APPEND, 0777);
			if (out < 0)
			{
				pr_error(strerror(errno), argv[i]);
				return (NULL);
			}
			if (dup2(out, STDOUT_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (NULL);
			}	
		}	
	}
	i = 0;
	while (ft_strcmp(argv[i], ">>") && argv[i] != NULL)
		i++;
	command = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ft_strcmp(argv[i], ">>") && argv[i] != NULL)
	{
		command[i] = ft_strdup(argv[i]);
		i++;
	}
	command[i] = NULL;
	return (command);	
}
