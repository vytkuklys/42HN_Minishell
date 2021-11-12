/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:24 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/16 21:41:15 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	ft_get_beggining_len(char const *s1, int *trim)
{
	int	beginning;

	beginning = 0;
	while (trim[(unsigned char)s1[beginning]])
		beginning++;
	return (beginning);
}

static int
	ft_get_ending_len(char const *s1, int *trim)
{
	int	ending;
	int	len;

	ending = 0;
	len = ft_strlen(s1) - 1;
	while (len > 0 && trim[(unsigned char)s1[len]])
	{
		len--;
		ending++;
	}
	return (ending);
}

static int
	*ft_get_deletable_chars(char const *set)
{
	static int	arr[256];

	ft_memset((void *)arr, 0, sizeof arr);
	while (*set != '\0')
		arr[(unsigned char)*set++] = 1;
	return (arr);
}

char
	*ft_strtrim(char const *s1, char const *set)
{
	int			*trim;
	int			start0end1len2[3];
	static char	*dup;
	char		*dup_copy;

	if (s1 == NULL)
		return (NULL);
	trim = ft_get_deletable_chars(set);
	start0end1len2[0] = ft_get_beggining_len(s1, trim);
	start0end1len2[1] = ft_get_ending_len(s1, trim);
	start0end1len2[2] = ft_strlen(s1) - start0end1len2[0] - start0end1len2[1];
	if (start0end1len2[2] < 0)
		start0end1len2[2] = 0;
	dup = (char *)malloc(start0end1len2[2] * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	dup_copy = dup;
	start0end1len2[1] = start0end1len2[0];
	while (start0end1len2[1] < (start0end1len2[2] + start0end1len2[0]))
	{
		*dup_copy++ = s1[start0end1len2[1]];
		start0end1len2[1]++;
	}
	*dup_copy++ = 0;
	return (dup);
}
