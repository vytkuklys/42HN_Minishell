/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:21 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/14 12:29:21 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char
	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	found;

	i = 0;
	found = -1;
	while (str[i])
	{
		if (str[i] == c)
			found = i;
		i++;
	}
	if (c == '\0' && str[i] == '\0')
		return ((char *)&str[i]);
	if (found != -1)
		return ((char *)&str[found]);
	return (0);
}
