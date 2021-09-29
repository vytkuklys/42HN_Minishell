/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:44 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/14 12:27:45 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void
	*ft_memset(void *str, int c, unsigned int n)
{
	unsigned int	i;
	unsigned char	*result;

	i = 0;
	result = str;
	if (n <= 0)
		return (str);
	while (i < n)
	{
		result[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
