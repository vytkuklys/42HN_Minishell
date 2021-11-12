/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:57 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/20 16:22:54 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_putnbr_fd(int n, int fd)
{
	char	num;
	long	copy_n;
	long	div;
	int		digits;

	if (n < 0)
		write(fd, "-", 1);
	if (n == -2147483648)
		copy_n = 2147483648;
	else if (n < 0)
	{
		n *= -1;
		copy_n = (long)n;
	}
	else
		copy_n = (long)n;
	digits = ft_get_digit_count(copy_n);
	while (digits > 0)
	{
		div = ft_pow(10, digits - 1);
		num = (copy_n / div) + '0';
		write(fd, &num, 1);
		copy_n %= div;
		digits--;
	}
}
