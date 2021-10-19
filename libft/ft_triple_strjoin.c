/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triple_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:29:21 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/19 18:49:16 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_triple_strjoin(char **s1, char const *s2, char const *s3, int len_s1)
{
	size_t	len_s2;
	size_t	len_s3;
	char	*p;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len_s2 = ft_strlen(s2);
	len_s3 = ft_strlen(s3);
	p = malloc((len_s1 + len_s2 + len_s3 + 1) * sizeof(char));
	if (p == NULL || *s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	ft_strlcpy(p, *s1, len_s1 + 1);
	ft_memcpy(p + len_s1, s2, len_s2);
	ft_memcpy(p + len_s1 + len_s2, s3, len_s3);
	p[len_s1 + len_s2 + len_s3] = '\0';
	free(*s1);
	*s1 = NULL;
	return (p);
}
