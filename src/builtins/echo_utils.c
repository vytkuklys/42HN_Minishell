/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:50:18 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/03 01:40:02 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int add_slashes(char **quote, char *start, int *j)
{
	int	i;

	if (start == NULL || *quote == NULL) //add clean exit / free stuff
		return (-1);
	i = 0;
	while (start && start[i] == '\\')
	{
		if (i % 2 == 0)
		{
			(*quote)[(*j)] = '\\';
			(*j)++;
		}
		i++;
	}
	return (i);
}
