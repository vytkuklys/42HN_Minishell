/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:55:45 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/01 01:47:18 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *free_str(char **str)
{
	if (*str == NULL)
		return (NULL);
	free(*str);
	*str = NULL;
	return (NULL);
}
