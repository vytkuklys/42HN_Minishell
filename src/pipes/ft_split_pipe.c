/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 12:37:23 by jludt             #+#    #+#             */
/*   Updated: 2021/10/13 14:11:23 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**do_split(char	**s_array, char const *s, char c, char *d)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
			i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
			i++;
		}
		if ((s[i] == c && s[i - 1] != '\\') || s[i + 1] == '\0')
		{
			if (s[i + 1] == '\0')
				s_array[k] = ft_substr(s, j, i - j + 1);
			else
				s_array[k] = ft_substr(s, j, i - j);
			s_array[k] = ft_strtrim(s_array[k], d);
			j = i + 1;
			k++;
		}
	}
	s_array[k] = NULL;
	return (s_array);
}

static int	num_splits(char *s, char c)
{
	int	i;
	int	splits;

	splits = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
			i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
			i++;
		}
		if (s[i] == c && s[i - 1] != '\\')
			splits++;
	}
	return (splits);
}

char	**ft_split_pipe(char *s, char c, char *d)
{
	char	**s_array;
	int		splits;

	if (s == 0)
		return (0);
	splits = num_splits(s, c);
	s_array = malloc(sizeof(char *) * (splits + 1));
	if (s_array == NULL)
		return (NULL);
	s_array = do_split(s_array, s, c, d);
	free(s);
	return (s_array);
}
