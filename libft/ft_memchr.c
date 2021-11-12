/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/19 21:50:00 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	c_copy;
	unsigned char	*str_copy;

	str_copy = (unsigned char *)str;
	c_copy = (unsigned char)c;
	while (n > 0)
	{
		if (*str_copy == c_copy)
			return ((void *)&*str_copy);
		str_copy++;
		n--;
	}
	return (0);
}
