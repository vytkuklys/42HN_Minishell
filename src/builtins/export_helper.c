/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:08:20 by julian            #+#    #+#             */
/*   Updated: 2021/10/20 13:15:09 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_sort(char *s[], int size)
{
	int		i;
	int		sort;
	char	*temp;

	i = 0;
	sort = 1;
	while (sort != 0)
	{
		sort = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(s[i], s[i + 1]) > 0)
			{
				temp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = temp;
				sort = 1;
			}
			i++;
		}
		i = 0;
	}
}

int	print_export(char *envp[])
{
	char	**envp_copy;
	int		i;
	int		j;

	i = 0;
	while (envp[i] != NULL)
		i++;
	envp_copy = (char **)malloc(sizeof(char *) * i + 1);
	if (envp_copy == NULL)
		return (0);
	j = -1;
	while (++j < i)
		envp_copy[j] = ft_strdup(envp[j]);
	envp_copy[j] = NULL;
	ft_sort(envp_copy, i);
	i = 0;
	while (envp_copy[i] != NULL)
		printf("declare -x %s\n", envp_copy[i++]);
	j = -1;
	while (++j < i)
		free(envp_copy[j]);
	free(envp_copy);
	return (1);
}
