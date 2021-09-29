/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:04:05 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/17 21:04:06 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_node *head)
{
	t_node	*current_node;

	current_node = head;
	while (current_node != NULL)
	{
		ft_putnbr_fd(current_node->num, 1);
		write(1, " ", 1);
		current_node = current_node->next;
	}
}
