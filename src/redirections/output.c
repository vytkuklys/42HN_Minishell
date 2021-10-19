/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:49:10 by jludt             #+#    #+#             */
/*   Updated: 2021/10/15 18:44:14 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**redirect_out(char **argv)
{
	int		i;
	int		out;

	i = -1;
	while (argv[++i] != NULL)
	{
		if (!ft_strcmp(argv[i], ">"))
		{
			i++;
			out = open(argv[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
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
	return (update_argv(argv, ">"));
}