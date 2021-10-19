/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:22:50 by julian            #+#    #+#             */
/*   Updated: 2021/10/14 15:54:33 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**update_argv(char **argv, char *redirection)
{
	int		i[3];
	char	**argv_updated;

	i[0] = 0;
	while (argv[i[0]] != NULL)
		i[0]++;
	argv_updated = (char **)malloc(sizeof(char *) * (i[0] - 1));
	if (argv_updated == NULL)
		return (NULL);
	i[0] = -1;
	i[2] = 0;
	i[1] = 0;
	while (argv[++i[0]] != NULL)
	{
		if (!ft_strcmp(argv[i[0]], redirection) && i[2] == 0)
		{
			i[0]++;
			i[2] = 1;
			continue ;
		}
		argv_updated[i[1]++] = ft_strdup(argv[i[0]]);
	}
	argv_updated[i[1]] = NULL;
	return (argv_updated);
}
