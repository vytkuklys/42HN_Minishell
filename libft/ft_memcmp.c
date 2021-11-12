/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:34 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/16 21:40:58 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int
	ft_memcmp(const void *str1, const void *str2, unsigned int n)
{
	unsigned char	*str1_copy;
	unsigned char	*str2_copy;

	str1_copy = (unsigned char *)str1;
	str2_copy = (unsigned char *)str2;
	while (n > 0)
	{
		if (*str1_copy > *str2_copy)
			return (*str1_copy - *str2_copy);
		if (*str2_copy > *str1_copy)
			return (*str1_copy - *str2_copy);
		str1_copy++;
		str2_copy++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*str1_copy - *str2_copy);
}
