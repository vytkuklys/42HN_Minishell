/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:55:45 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/01 15:30:55 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char ***arr)
{
	int		i;
	char	**tmp;

	tmp = *arr;
	if (tmp == NULL)
		return ;
	i = 0;
	while (tmp != NULL && tmp[i] != NULL)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	*arr = NULL;
}

char	*free_str(char **str)
{
	if (*str == NULL)
		return (NULL);
	free(*str);
	*str = NULL;
	return (NULL);
}

int	free_data(t_var **data, char **cmd)
{
	free_str(cmd);
	free_array(&(*data)->env);
	free(*data);
	write(1, "exit\n", 6);
	return (0);
}

void	free_argv(char ***argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != NULL)
			free(argv[i][j++]);
		free(argv[i++]);
	}
	free(argv);
}
