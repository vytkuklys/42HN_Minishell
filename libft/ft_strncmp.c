/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:15 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/07 21:45:01 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*b2;
	unsigned char	*b1;

	b2 = (unsigned char *)s2;
	b1 = (unsigned char *)s1;
	if (n == 0)
		return (0);
	while (*b1 == *b2 && *b1 != '\0' && n > 1)
	{
		n--;
		b2++;
		b1++;
	}
	if (*b1 == *b2)
		return (0);
	else
		return (*b1 - *b2);
}
