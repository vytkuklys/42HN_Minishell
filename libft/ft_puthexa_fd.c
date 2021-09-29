/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:10:02 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/21 20:00:12 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_hexa_length(unsigned long n)
{
	int	length;

	length = 0;
	if (n == 0)
		length = 1;
	while (n > 0)
	{
		n /= 16;
		length++;
	}
	return (length);
}

int	ft_puthexa_fd(unsigned long n, int fd, int upper)
{
	int		rem;
	char	hexa[45];
	int		i;
	int		length;

	length = ft_get_hexa_length(n);
	i = 1;
	if (n == 0)
		hexa[length - 1] = '0';
	while (n > 0)
	{
		rem = n % 16;
		if (rem > 9 && !upper)
			hexa[length - i] = rem + 87;
		else if (rem > 9 && upper)
			hexa[length - i] = rem + 55;
		else
			hexa[length - i] = rem + 48;
		n /= 16;
		i++;
	}
	hexa[length] = '\0';
	ft_putstr_fd(hexa, fd);
	return (length);
}
