/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:41 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/18 16:34:13 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memmove(void *dst, const void *src, unsigned int length)
{
	unsigned char	*src_copy;
	unsigned char	*dest_copy;

	if (dst == 0 && src == 0)
		return (0);
	if (length <= 0)
		return (dst);
	if (dst <= src)
		return (ft_memcpy(dst, src, length));
	src_copy = (unsigned char *)src + length - 1;
	dest_copy = dst + length - 1;
	while (length > 0)
	{
		*dest_copy = *src_copy;
		dest_copy--;
		src_copy--;
		length--;
	}
	return (dst);
}
