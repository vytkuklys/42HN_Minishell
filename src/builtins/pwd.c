
   
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:21:24 by julian            #+#    #+#             */
/*   Updated: 2021/10/06 12:30:21 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
    char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
