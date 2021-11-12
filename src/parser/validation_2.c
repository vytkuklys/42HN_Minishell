/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 05:46:15 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/26 21:37:21 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	throw_invalid_error(t_var **data)
{
	printf("minishell: invalid command line arguments\n");
	(*data)->status = 1;
	return (0);
}
