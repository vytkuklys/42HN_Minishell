/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:28:56 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/16 21:41:13 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int
	ft_is_appendable(char *dst, unsigned int size)
{
	while (*dst && size > 0)
	{
		dst++;
		size--;
	}
	return (size);
}

unsigned int
	ft_strlcat(char *dst, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	if (ft_is_appendable(dst, size) == 0)
		return (size + ft_strlen(src));
	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	if (size > i)
	{
		while (size - 1 - i > 0 && src[j] != '\0')
		{
			dst[j + i] = src[j];
			size--;
			j++;
		}
		dst[i + j] = '\0';
	}
	else
		i = size;
	while (src[j] != '\0')
		j++;
	return (i + j);
}
