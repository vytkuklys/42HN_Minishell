/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:18:12 by vkuklys           #+#    #+#             */
/*   Updated: 2021/08/02 21:37:49 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int
	ft_strl(const char *str)
{
	int	count;

	count = 0;
	if (!str || str == NULL)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

int
	ft_strncmp(const char *str1, const char *str2, unsigned int n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	while (*s1 != '\0' && *s2 != '\0' && n > 0)
	{
		if (*s1 > *s2)
			return (*s1 - *s2);
		if (*s2 > *s1)
			return (*s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}

void
	*ft_calloc(unsigned int num, unsigned int size)
{
	unsigned int	n;
	char			*p;

	n = num * size;
	p = (char *)malloc(n);
	if (p == 0)
		return (0);
	while (n > 0)
	{
		p[n - 1] = 0;
		n--;
	}
	return (p);
}

char
	*ft_strjoin(char **s1, const char *s2)
{
	int			i;
	char		*dup;
	char		*dup_copy;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	dup = (char *)malloc((ft_strl(*s1) + ft_strl(s2)) * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	dup_copy = dup;
	while (*s1 && (*s1)[i] != '\0')
		*dup_copy++ = (*s1)[i++];
	i = 0;
	while (s2[i] != '\0')
	{
		*dup_copy++ = s2[i];
		i++;
	}
	*dup_copy++ = '\0';
	free(*s1);
	*s1 = NULL;
	return (dup);
}

char
	*ft_strjoin1(char **s1, const char **s2)
{
	int			i;
	char		*dup;
	char		*dup_copy;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	dup = (char *)malloc((ft_strl(*s1) + ft_strl(*s2)) * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	dup_copy = dup;
	while (*s1 && (*s1)[i] != '\0')
		*dup_copy++ = (*s1)[i++];
	i = 0;
	while ((*s2)[i] != '\0')
	{
		*dup_copy++ = (*s2)[i];
		i++;
	}
	*dup_copy++ = '\0';
	free(*s1);
	*s1 = NULL;
	return (dup);
}
