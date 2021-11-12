/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_int_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:20:06 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/21 20:01:42 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_put_unsigned_int_fd(unsigned int n, int fd)
{
	char			num;
	unsigned int	copy_n;
	unsigned int	div;
	int				digits;
	int				copy_digits;

	copy_n = (long)n;
	digits = ft_get_digit_count(copy_n);
	copy_digits = digits;
	while (digits > 0)
	{
		div = ft_pow(10, digits - 1);
		num = (copy_n / div) + '0';
		write(fd, &num, 1);
		copy_n %= div;
		digits--;
	}
	return (copy_digits);
}
