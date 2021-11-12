/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:54:38 by jludt             #+#    #+#             */
/*   Updated: 2021/10/22 15:54:46 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_dollar_num(const char *s)
{
	int	i;
	int	dollars;

	i = 0;
	dollars = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == '$')
			dollars++;
		i++;
	}
	return (dollars);
}
