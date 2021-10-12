/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:44:16 by julian            #+#    #+#             */
/*   Updated: 2021/10/07 14:45:33 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_memory(char *src)
{
	int	i[2];

	i[0] = -1;
	i[1] = 0;
	while (src[++i[0]] != '\0')
	{
		if (src[i[0]] == '"')
		{
			i[0]++;
			while (src[i[0]] != '"' && src[i[0]] != '\0')
				i[0]++;
			i[0]++;
		}
		if (src[i[0]] == '\'')
		{
			i[0]++;
			while (src[i[0]] != '\'' && src[i[0]] != '\0')
				i[0]++;
			i[0]++;
		}
		if (src[i[0]] == '\\' && src[i[0] + 1] == '|')
			i[0] += 2;
		i[1]++;
	}
	return (i[1]);
}

void static	trim_string(char *src, char *s)
{
	int	i[2];

	i[0] = -1;
	i[1] = 0;
	while (src[++i[0]] != '\0')
	{
		if (src[i[0]] == '"')
		{
			i[0]++;
			while (src[i[0]] != '"' && src[i[0]] != '\0')
				i[0]++;
			i[0]++;
		}
		if (src[i[0]] == '\'')
		{
			i[0]++;
			while (src[i[0]] != '\'' && src[i[0]] != '\0')
				i[0]++;
			i[0]++;
		}
		if (src[i[0]] == '\\' && src[i[0] + 1] == '|')
			i[0] += 2;
		s[i[1]++] = src[i[0]];
	}
	s[i[1]] = '\0';
}

/*
** pipes are not considered if they are escaped or in quotes
*/

char	*trim_pipes(char *src)
{
	char	*s;
	int		i;

	i = get_memory(src);
	s = (char *)malloc(sizeof(char) * i + 1);
	if (s == NULL)
		return (NULL);
	trim_string(src, s);
	return (s);
}
