/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:22:50 by julian            #+#    #+#             */
/*   Updated: 2021/11/05 10:58:00 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_2d(char ***argv)
{
	int	j;

	j = 0;
	while (argv[0][j] != NULL)
		free(argv[0][j++]);
	free(argv[0]);
}

void	update_argv(char ***argv, char *redirection, int pos)
{
	int		i[3];
	char	**argv_updated;

	i[0] = 0;
	while (argv[pos][i[0]] != NULL)
		i[0]++;
	argv_updated = (char **)malloc(sizeof(char *) * (i[0] - 1));
	if (argv_updated == NULL)
		return ;
	ft_memset(i, 0, 12);
	i[0] = -1;
	while (argv[pos][++i[0]] != NULL)
	{
		if (!ft_strcmp(argv[pos][i[0]], redirection) && i[2] == 0)
		{
			i[0]++;
			i[2] = 1;
			continue ;
		}
		argv_updated[i[1]++] = ft_strdup(argv[pos][i[0]]);
	}
	argv_updated[i[1]] = NULL;
	free_2d(&argv[pos]);
	argv[pos] = NULL;
	argv[pos] = argv_updated;
}
