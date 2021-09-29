/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:27 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/16 15:43:04 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t			i;
	size_t			length;
	static char		*dup;
	char			*dup_copy;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	dup = (char *)malloc(len * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	dup_copy = dup;
	i = 0;
	while (s[0] != '\0' && i < len && s[start + i] != '\0' && start < length)
	{
		dup_copy[i] = s[start + i];
		i++;
	}
	dup_copy[i] = '\0';
	return (dup);
}
