/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:55:45 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/13 04:22:10 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_2d_array(char ***arr)
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
	free_2d_array(&(*data)->env);
	free_2d_array(&(*data)->history);
	free(*data);
	return (0);
}