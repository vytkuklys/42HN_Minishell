/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:28:05 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/16 19:20:12 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	ft_get_strings_num(char const *s, char c)
{
	int	i;
	int	num;
	int	delimiter;

	i = 0;
	num = 0;
	delimiter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			delimiter++;
		else if (delimiter > 0 && i - delimiter > 0)
		{
			delimiter = 0;
			num++;
		}
		else if (i - delimiter == 0)
			delimiter = 0;
		i++;
	}
	if (i - delimiter > 0)
		num++;
	return (num);
}

static unsigned int
	ft_get_ending_num(const char *s, char c)
{
	unsigned int	end;

	end = 0;
	while (s[end] != c && s[end] != '\0')
		end++;
	return (end);
}

static int
	ft_add_strings(char **arr, char const *s, char c)
{
	int	jk[2];
	int	length;

	jk[0] = 0;
	jk[1] = 0;
	length = 0;
	while (s[jk[1]] != '\0')
	{
		if (s[jk[1]] != c)
		{
			length = ft_get_ending_num(&s[jk[1]], c);
			arr[jk[0]] = ft_substr(s, jk[1], length);
			if (arr[jk[0]] == NULL)
			{
				ft_free_2d_array(&arr, jk[0]);
				return (0);
			}
			jk[1] += length;
			jk[0]++;
		}
		else
			jk[1]++;
	}
	return (1);
}

char
	**ft_split(char const *s, char c)
{
	int			len;
	static char	**dup;
	char		**dup_copy;

	if (s == NULL)
		return (NULL);
	len = ft_get_strings_num(s, c);
	dup = (char **)malloc((len + 1) * sizeof(char *));
	if (dup == NULL)
		return (NULL);
	if (!ft_add_strings(dup, s, c))
		return (NULL);
	dup_copy = dup;
	dup_copy[len] = 0;
	return (dup);
}
