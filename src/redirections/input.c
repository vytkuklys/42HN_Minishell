/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:49:48 by jludt             #+#    #+#             */
/*   Updated: 2021/10/13 14:49:50 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**redirect_in(char **argv)
{
	int		i;
	int		j;
	int		in;
	int		arr_len;
	char	**command;

	arr_len = 0;
	while (argv[++arr_len] != NULL)
		arr_len++;
	i = -1;
	while (argv[++i] != NULL)
	{
		if (!ft_strcmp(argv[i], "<"))
		{
			i++;
			in = open(argv[i], O_RDONLY);
			if (in < 0)
			{
				pr_error(strerror(errno), argv[i]);
				return (NULL);
			}
			if (dup2(in, STDIN_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (NULL);
			}	
		}	
	}
	i = 0;
	while (ft_strcmp(argv[i], "<") && argv[i] != NULL)
		i++;
	command = (char **)malloc(sizeof(char *) * (arr_len - i - 1));
	j = 0;
	while (argv[i + 2] != NULL)
	{
		command[j++] = ft_strdup(argv[i + 2]);
		i++;
	}
	command[j] = NULL;
	return (command);	
}
