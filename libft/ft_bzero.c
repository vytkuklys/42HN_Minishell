/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:26:53 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/19 20:52:35 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void
	ft_bzero(void *dst, unsigned int n)
{
	unsigned int	i;
	unsigned char	*result;

	i = 0;
	result = dst;
	while (i < n)
	{
		result[i] = '\0';
		i++;
	}
}
