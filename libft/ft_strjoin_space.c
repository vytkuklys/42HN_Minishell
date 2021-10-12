/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:19:58 by jludt             #+#    #+#             */
/*   Updated: 2021/10/12 13:45:32 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_space(char **src)
{
	int		i;
	char	*s_join;

	if (*src == NULL || src == NULL)
		return (NULL);
	s_join = ft_calloc(1, 1);
	i = -1;
	while (src[++i] != NULL)
	{
		s_join = ft_strjoin(&s_join, src[i]);
		if (src[i + 1] != NULL)
			s_join = ft_strjoin(&s_join, " ");
	}
	return (s_join);
}
