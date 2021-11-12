/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:35:29 by jludt             #+#    #+#             */
/*   Updated: 2021/10/25 09:00:33 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
** specified in ’set’ removed from the beginning and the end of the string.
** parameters:
** s1 - The string to be trimmed.
** s2 - The reference set of characters to trim.
** return value:
** The trimmed string. NULL if the allocation fails.
*/

char	*ft_strtrim_free(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != 0)
		start++;
	end = ft_strlen(s1);
	while (end > 0 && ft_strchr(set, s1[end]) != 0)
		end--;
	if (start >= end)
		return (ft_strdup(""));
	return (ft_substr_free(s1, start, end - start + 1));
}
