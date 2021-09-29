/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:15 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/29 00:07:53 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if (!n || ft_strlen(str2) != n)
		return (0);
	if (!n)
		return (0);
	i = 0;
	while (i < n - 1 && *(str1 + i) && *(str1 + i) == *(str2 + i) && *(str2 + i))
		i++;
	return (*((unsigned char *)str1 + i) - *((unsigned char *)str2 + i));
}

