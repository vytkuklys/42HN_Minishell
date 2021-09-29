/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:27:26 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/20 16:03:29 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long
	ft_get_reverse_num(int n)
{
	long long	num;

	num = 0;
	if (n == -2147483648)
		num = 8463847412;
	else if (n < 0)
		n *= -1;
	while (n > 0)
	{
		num *= 10;
		num += n % 10;
		n /= 10;
	}
	return (num);
}

int
	ft_get_digit_count(long long n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		digits++;
	if (n < 0)
	{
		n *= -1;
		digits++;
	}
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static int
	ft_get_zeros(int n, long long reverse)
{
	int	reverseDigits;
	int	nDigits;

	reverseDigits = ft_get_digit_count(reverse);
	nDigits = ft_get_digit_count(n);
	if (n < 0)
		nDigits--;
	if (n == 0)
		return (1);
	return (nDigits - reverseDigits);
}

char
	*ft_itoa(int n)
{
	long long		reverse;
	int				zeros;
	static char		*dup;
	char			*dup_copy;

	reverse = ft_get_reverse_num(n);
	zeros = ft_get_zeros(n, reverse);
	dup = (char *)malloc(ft_get_digit_count(n) * sizeof(char) + 1);
	if (dup == 0)
		return (0);
	dup_copy = dup;
	if (n < 0)
		*dup_copy++ = '-';
	while (reverse > 0)
	{
		*dup_copy++ = (reverse % 10) + '0';
		reverse /= 10;
	}
	while (zeros > 0)
	{
		*dup_copy++ = '0';
		zeros--;
	}
	*dup_copy++ = '\0';
	return (dup);
}
