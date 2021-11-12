/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:02 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/30 21:36:25 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	if (!str || str == NULL)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}
