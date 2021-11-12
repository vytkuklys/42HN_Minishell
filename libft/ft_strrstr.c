/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:21:00 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/30 23:12:43 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrstr(const char *big, const char *lil)
{
	int	i;
	int	j;
	int	lil_len;

	if (lil[0] == '\0' || lil == NULL)
		return (-1);
	lil_len = ft_strlen(lil);
	i = 0;
	while (big && big[i] != '\0')
	{
		if (big[i] == lil[0])
		{
			j = 0;
			while (big[i + j] != '\0' && big[i + j] == lil[j] && j < lil_len)
				j++;
			if (j == lil_len)
				return (i);
		}
		i++;
	}
	return (-1);
}
