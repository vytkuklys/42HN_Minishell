/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:21:00 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/16 22:54:04 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strnstr(const char *big, const char *lil, size_t l)
{
	size_t	i;
	size_t	len;

	if (lil[0] == '\0' || lil == NULL)
		return ((char *)big);
	len = ft_strlen(lil);
	while (*big && l > 0)
	{
		if (*big == *lil)
		{
			i = 0;
			while (big[i] != '\0' && big[i] == lil[i] && i < len && l > 0)
			{
				i++;
				l--;
			}
			if (i == len)
				return ((char *)big);
			else
				l += i;
		}
		l--;
		big++;
	}
	return (NULL);
}
