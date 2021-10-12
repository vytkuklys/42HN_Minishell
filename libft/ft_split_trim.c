/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_trim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 12:37:23 by jludt             #+#    #+#             */
/*   Updated: 2021/10/11 17:20:39 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_split(char const *s, char c, int i)
{
	int	split;

	split = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			split++;
		i++;
	}
	return (split);
}

static char	**do_split(char	**s_array, char const *s, char c, int i, char *d)
{
	int		j;
	int		k;
	int		s_num;

	s_num = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		s_array[s_num] = malloc(sizeof(char) * j + 1);
		if (s_array[s_num] == NULL)
			return (NULL);
		j = i + j;
		k = 0;
		while (i < j)
			s_array[s_num][k++] = s[i++];
		s_array[s_num][k] = '\0';
		s_array[s_num] = ft_strtrim(s_array[s_num], d);
		s_num++;
		while (s[i] != '\0' && s[i] == c)
			i++;
	}
	s_array[s_num] = NULL;
	return (s_array);
}

char	**ft_split_trim(char const *s, char c, char *d)
{
	char	**s_array;
	int		i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	s_array = malloc(sizeof(char *) * (num_split(s, c, i) + 2));
	if (s_array == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	s_array = do_split(s_array, s, c, i, d);
	return (s_array);
}
