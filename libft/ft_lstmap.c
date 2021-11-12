/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:08:31 by vkuklys           #+#    #+#             */
/*   Updated: 2021/09/17 21:04:48 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

	/*list = NULL;
	len = ft_lstsize(lst);
	while (len > 0)
	{
		content = (*f)(lst->num);
		item = ft_lstnew(content);
		if (item == NULL)
		{
			ft_lstclear(&list, (*dl)(list));
			free(list);
			return (NULL);
		}
		ft_lstadd_back(&list, item);
		lst = lst->next;
		len--;
	}*/

t_node
	*ft_lstmap(t_node *lst, int (*f)(int), int (*dl)(t_node *))
{
	t_node	*list;
	t_node	*item;
	int		content;
	int		len;

	if (lst == NULL)
		return (NULL);
	return (list);
}
