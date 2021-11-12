/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:28:46 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/14 16:45:09 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strdup(const char *str1)
{
	int			count;
	static char	*dup;
	char		*dup_copy;

	count = ft_strlen(str1);
	dup = (char *)malloc(count * sizeof(char) + 1);
	if (dup == 0)
		return (0);
	dup_copy = dup;
	while (*str1 != '\0')
		*dup_copy++ = *str1++;
	*dup_copy = '\0';
	return (dup);
}
