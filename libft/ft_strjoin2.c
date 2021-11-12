/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:28:53 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/13 14:02:32 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin2(char **s1, const char *s2)
{
	int			i;
	char		*dup;
	char		*dup_copy;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	dup = (char *)malloc((ft_strlen(*s1) + ft_strlen(s2)) * sizeof(char) + 1);
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
	return (dup);
}
