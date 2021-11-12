/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:47:36 by jludt             #+#    #+#             */
/*   Updated: 2021/11/04 13:13:15 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_one(char *s, t_var **data)
{
	int	len;

	len = ft_strlen(s);
	if (len == 3)
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		(*data)->status = 258;
		return (0);
	}
	if (len > 3)
	{
		printf("minishell: syntax error near unexpected token `>>'\n");
		(*data)->status = 258;
		return (0);
	}
	return (1);
}

static int	handle_two(char *s, t_var **data)
{
	int	len;

	len = ft_strlen(s);
	if (len >= 3)
	{
		if (len == 3)
			printf("minishell: syntax error near unexpected token `<'\n");
		else if (len == 4)
			printf("minishell: syntax error near unexpected token `<<'\n");
		else if (len > 4)
			printf("minishell: syntax error near unexpected token `<<<'\n");
		(*data)->status = 258;
		return (0);
	}
	return (1);
}

int	check_redirections(char **argv, t_var **data)
{
	int	i;

	i = -1;
	while (argv[++i] != NULL)
	{
		if (!ft_strncmp(argv[i], ">>", 2))
			if (!handle_one(argv[i], data))
				return (0);
		if (!ft_strncmp(argv[i], "<<", 2))
			if (!handle_two(argv[i], data))
				return (0);
	}
	return (1);
}
