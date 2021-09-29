/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:08:40 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/14 22:07:59 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_lstsize(t_node *lst)
{
	int	count;

	count = 1;
	if (lst == NULL)
		return (0);
	else if (lst->next == NULL)
		return (count);
	while (lst->next != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
