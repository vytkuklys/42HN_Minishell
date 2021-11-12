/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:08:14 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/16 17:06:19 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_node
// 	*ft_lstclear(t_node **lst)
// {
// 	t_node	*tmp;
// 	t_node	*tmp2;

// 	if (*lst == NULL || (*del) == NULL)
// 		return (NULL);
// 	tmp2 = *lst;
// 	while (tmp2->next != NULL)
// 	{
// 		tmp = tmp2->next;
// 		(*del)(tmp2);
// 		free(tmp2);
// 		tmp2 = tmp;
// 	}
// 	(*del)(tmp2);
// 	free(tmp2);
// 	*lst = NULL;
// 	return (NULL);
// }

t_node
	*ft_lstclear(t_node **lst)
{
	t_node	*tmp;
	t_node	*tmp2;

	if (*lst == NULL)
		return (NULL);
	tmp2 = *lst;
	while (tmp2 != NULL)
	{
		tmp = tmp2->next;
		free(tmp2);
		tmp2 = tmp;
	}
	*lst = NULL;
	return (NULL);
}
