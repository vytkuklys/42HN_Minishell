/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:02 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/28 23:40:46 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(unsigned int num, unsigned int size)
{
	unsigned int	n;
	char			*p;

	n = num * size;
	p = (char *)malloc(n);
	if (p == 0)
		return (0);
	while (n > 0)
	{
		p[n - 1] = 0;
		n--;
	}
	return (p);
}
