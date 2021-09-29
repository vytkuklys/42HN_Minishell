/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:37 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/16 21:41:02 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void
	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned char	*src_copy;
	unsigned char	*dest_copy;

	if (dest == 0 && src == 0)
		return (0);
	src_copy = (unsigned char *)src;
	dest_copy = dest;
	while (n > 0)
	{
		*dest_copy = *src_copy;
		dest_copy++;
		src_copy++;
		n--;
	}
	return (dest);
}
