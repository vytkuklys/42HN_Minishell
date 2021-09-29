/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:26:45 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/17 21:06:08 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int
	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f')
		return (1);
	else if (c == '\r' || c == '\n')
		return (1);
	else
		return (0);
}

static int
	ft_check_beginning_before_numbers(const char *s)
{
	int	space;
	int	plus;
	int	minus;
	int	i;

	i = 0;
	space = 0;
	plus = 0;
	minus = 0;
	while (!(s[i] >= 48 && s[i] <= 57))
	{
		if (ft_is_space(s[i]))
			space++;
		else if (s[i] == '+')
			plus++;
		else if (s[i] == '-')
			minus++;
		else
			return (-1);
		if ((ft_is_space(s[i]) && (plus || minus)) || plus > 1 || minus > 1
			|| minus + plus > 1)
			return (-1);
		i++;
	}
	return (i);
}

static int
	ft_is_minus(const char *str)
{
	int	i;
	int	minus;

	i = 0;
	minus = 0;
	while (!(str[i] >= 48 && str[i] <= 57))
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	return (minus);
}

static int
	ft_is_min_max_valid(int index, int symbols, int minus)
{
	int	digits;

	digits = index - symbols;
	if (digits >= 19 && minus == 1)
		return (0);
	else if (digits >= 20 && minus == 0)
		return (-1);
	return (2);
}

long long
	ft_atoi(const char *str)
{
	long long		num;
	int				i;
	int				minus;
	int				minMax;
	int				symbols;

	num = 0;
	i = 0;
	symbols = ft_check_beginning_before_numbers(str);
	if (symbols == -1)
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[symbols + i] >= 48 && str[symbols + i] <= 57))
			break ;
		num = (num * 10) + (str[symbols + i] - '0');
		i++;
	}
	minus = ft_is_minus(str);
	minMax = ft_is_min_max_valid(i, symbols, minus);
	if (minMax == -1 || minMax == 0)
		return (minMax);
	if (minus == 1)
		return (num * -1);
	return (num);
}
