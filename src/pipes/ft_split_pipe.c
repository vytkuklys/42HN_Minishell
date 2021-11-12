/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 12:37:23 by jludt             #+#    #+#             */
/*   Updated: 2021/11/02 16:33:26 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	helper(int i, char *s)
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
	return (i);
}

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
		i = helper(i, (char *)s);
		if ((s[i] == c && s[i - 1] != '\\') || s[i + 1] == '\0')
		{
			if (s[i + 1] == '\0')
			{
				s_array[k] = ft_substr(s, j, i - j + 1);
			}
			else
				s_array[k] = ft_substr(s, j, i - j);
			d = "lorem ipsum";
			j = i + 1;
			k++;
		}
	}
	s_array[k] = NULL;
	return (s_array);
}

char	**ft_split_pipe(char *s, char c, char *d)
{
	char	**s_array;
	int		splits;

	if (s == 0)
		return (0);
	splits = count_pipes(s);
	s_array = (char **)malloc(sizeof(char *) * (splits + 2));
	if (s_array == NULL)
		return (NULL);
	s_array = do_split(s_array, s, c, d);
	return (s_array);
}

char	**handle_split_at_pipes(char *cmd_line, t_var **data)
{
	char	**s;

	if ((*data)->pipes == 0)
	{
		s = (char **)malloc(sizeof(char *) * 2);
		if (s == NULL)
			return (NULL);
		s[0] = ft_strdup(cmd_line);
		s[1] = NULL;
	}
	else
		s = ft_split_pipe(cmd_line, '|', " ");
	return (s);
}
