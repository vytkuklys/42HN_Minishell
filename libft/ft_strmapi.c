/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:10 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/16 14:16:44 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int			len;
	int			i;
	static char	*dup;
	char		*dup_copy;

	if (s == NULL || (*f) == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	dup = (char *)malloc(len * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	dup_copy = dup;
	while (s[i] != '\0')
	{
		dup_copy[i] = (*f)(i, s[i]);
		i++;
	}
	dup_copy[i] = '\0';
	return (dup);
}
