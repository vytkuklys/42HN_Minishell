/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:49:48 by jludt             #+#    #+#             */
/*   Updated: 2021/10/15 18:44:06 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**redirect_in(char **argv)
{
	int		i;
	int		in;

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
	return (update_argv(argv, "<"));
}
